#include "CustomGraphicsView.h"
#include <QGraphicsProxyWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDataStream>
#include <arrowlineitem.h>
#include <QMessageBox>
#include <QIcon>
#include <QInputDialog>
#include <addcommand.h>
#include <QDebug>
#include <QApplication>
#include <QDomDocument>
#include <QBuffer>


CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , currentLine(nullptr)
    , UndoStack(new QUndoStack(this))
{
    setScene(scene);
    setAcceptDrops(true);
    setRenderHints(QPainter::HighQualityAntialiasing);

    scene->setSceneRect(0, 0,600,400);

    acnSave = new QAction(tr("Save Not Yet Implemented"), this);
    acnDel = new QAction(tr("Delete line"), this);
    acnSetVal = new QAction(tr("Set value"), this);

    connect(acnSave, &QAction::triggered, this, &CustomGraphicsView::onActionSave);
    connect(acnDel, &QAction::triggered, this, &CustomGraphicsView::onActionDelete);
    connect(acnSetVal, &QAction::triggered, this, &CustomGraphicsView::onSetValue);

    connect(this, &CustomGraphicsView::UndoTriggered, UndoStack, &QUndoStack::undo);
    connect(this, &CustomGraphicsView::RedoTriggered, UndoStack, &QUndoStack::redo);

}

void CustomGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        event->acceptProposedAction();
    }
}

void CustomGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        event->acceptProposedAction();
    }
}

void CustomGraphicsView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QByteArray encodedData = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

        QIcon icon = qvariant_cast<QIcon>(roleDataMap[Qt::UserRole + 1]);
        QPixmap pixmap = icon.pixmap(64, 64);
        CustomPixmapItem* item = new CustomPixmapItem(pixmap);
        item->setPos(mapToScene(event->pos()));
        scene->addItem(item);
        connect(item, &CustomPixmapItem::positionChanged, this, &CustomGraphicsView::updateLinePosition);

        EmitDebugData(event->pos());
        AddItemToAddStack(item);

        event->acceptProposedAction();
    }

}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem *item = scene->itemAt(scenePos, QTransform());

    if (item && dynamic_cast<QGraphicsEllipseItem *>(item))
    {
        lineStartPoint = scenePos;
        currentLine = new ArrowLineItem(QLineF(lineStartPoint, lineStartPoint));
        scene->addItem(currentLine);
        lineConnections[currentLine].first = dynamic_cast<QGraphicsEllipseItem *>(item);
        currentLine->SetStartCircle(dynamic_cast<QGraphicsEllipseItem *>(item));
        item->parentItem()->setFlag(QGraphicsItem::ItemIsMovable, false);
        currentLine->SetStartCircleAttributes();
    }

    if (item && dynamic_cast<QGraphicsProxyWidget *>(item))
    {
        itemStartPosition = dynamic_cast<QGraphicsProxyWidget *>(item)->scenePos();
        emit PublishNewData(QString("(%1, %2)").arg(scenePos.x()).arg(scenePos.y()));
    }

    QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (currentLine)
    {
        QLineF newLine(lineStartPoint, mapToScene(event->pos()));
        currentLine->setLine(newLine);
    }

    update();
    QGraphicsView::mouseMoveEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (currentLine)
    {
        lineConnections[currentLine].first->parentItem()->setFlag(QGraphicsItem::ItemIsMovable, true);

        QPointF scenePos = mapToScene(event->pos());
        QList<QGraphicsItem *>items = scene->items(scenePos);

        bool lineDrawn = false;
        for(auto item:items)
        {
            auto test = dynamic_cast<QGraphicsEllipseItem *>(item);
            if (item && test)
            {
                QLineF newLine(lineStartPoint, scenePos);
                currentLine->setLine(newLine);
                lineConnections[currentLine].second = dynamic_cast<QGraphicsEllipseItem *>(item);
                currentLine->SetEndCircle(dynamic_cast<QGraphicsEllipseItem *>(item));
                currentLine->SetEndCircleAttributes();
                lineDrawn = true;
                break;
            }
        }

        if(!lineDrawn || (lineConnections[currentLine].first->parentItem() == lineConnections[currentLine].second->parentItem()))
        {
            scene->removeItem(currentLine);
            lineConnections.remove(currentLine);
            delete currentLine;
        }
        else
        {
            AddItemToAddStack(currentLine);
        }


        currentLine = nullptr;
    }
    else
    {
        QPointF scenePos = mapToScene(event->pos());
        QList<QGraphicsItem *>items = scene->items(scenePos);
        for(QGraphicsItem *itm:items)
        {
            CustomPixmapItem *cpItm = dynamic_cast<CustomPixmapItem *>(itm);
            if(cpItm)
            {
                emit PublishNewData(QString("(%1, %2)").arg(cpItm->pos().x()).arg(cpItm->pos().y()));
                AddItemToMoveStack(cpItm);

                break;
            }
        }
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void CustomGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    contextMenu.clear();
    QList<QGraphicsItem *> lst = items(event->pos());
    for(QGraphicsItem* item:lst)
    {
        CustomPixmapItem *widget = dynamic_cast<CustomPixmapItem *>(item);
        if(widget)
        {
            contextMenu.addAction(acnSetVal);
            selectedItem = widget;
        }
    }
    contextMenu.exec(event->globalPos());
}

void CustomGraphicsView::updateLinePosition()
{
    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
    {
        QGraphicsLineItem *line = it.key();
        QGraphicsEllipseItem *StartCircle = it.value().first;
        QGraphicsEllipseItem *EndCircle = it.value().second;

        if (StartCircle && EndCircle)
        {
            line->setLine(QLineF(StartCircle->scenePos(), EndCircle->scenePos()));
        }
    }
}

void CustomGraphicsView::ClearScene()
{
    RemoveAllLines();
    scene->clear();
    UndoStack->clear();
    emit PublishUndoData(QString());
    emit PublishRedoData(QString());
    emit PublishNewData(QString());
    emit PublishOldData(QString());
}

void CustomGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    contextMenu.clear();
    ArrowLineItem *line = dynamic_cast<ArrowLineItem *>(itemAt(event->pos()));
    if (line)
    {
        // Add actions to the context menu
        contextMenu.addAction(acnSave);
        contextMenu.addAction(acnDel);
        selectedItem = line;
        // Show the context menu at the cursor position
    }
    contextMenu.exec(event->globalPos());
}

void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);
    double scalefactor = 1.5;

    if(event->modifiers() & Qt::ControlModifier)
    {
        if(event->delta() > 0)
        {
           scale(scalefactor,scalefactor);
        }
        else
        {
            scale(1/scalefactor,1/scalefactor);
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

void CustomGraphicsView::onActionSave()
{
    // Action 1 triggered
}

//remove lines and break connections . Remember to delete pointers
void CustomGraphicsView::RemoveLines()
{
    ArrowLineItem * arrowLine = dynamic_cast<ArrowLineItem *>(selectedItem);
    lineConnections.remove(arrowLine);
}

//remove lines and break connections . Remember to delete pointers
void CustomGraphicsView::RemoveAllLines()
{
    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
    {
        delete it.key();
    }
    lineConnections.clear();
}

void CustomGraphicsView::onActionDelete()
{
    if (selectedItem)
    {
        scene->removeItem(selectedItem);
        RemoveLines();
        delete selectedItem;
        selectedItem = nullptr;
    }
}

void CustomGraphicsView::onSetValue()
{
    CustomPixmapItem* item = dynamic_cast<CustomPixmapItem *>(selectedItem);
    if(item)
    {
        double value = QInputDialog::getDouble(this, "Enter Value:", "Operation:", 0, 0, 1000, 2, nullptr);
        item->SetText(QString::number(value));
    }

}

void CustomGraphicsView::onResult()
{
    double result = 0.0;

    QSet<CustomPixmapItem*> visitItems;

    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
    {
        QGraphicsEllipseItem *startEllipse = it.value().first;
        QGraphicsEllipseItem *endEllipse = it.value().second;

        if (startEllipse && endEllipse)
        {
            CustomPixmapItem *startItem = dynamic_cast<CustomPixmapItem *>(startEllipse->parentItem());
            CustomPixmapItem *endItem = dynamic_cast<CustomPixmapItem *>(endEllipse->parentItem());

            int endId = endItem->GetItemId();
            int n;
            if(endId > 4)
            {
                n = endId % 4;
            }
            else
            {
                n = endId;
            }
            switch(n)
            {
            case 1 :
                result += startItem->GetText().toDouble() +  endItem->GetText().toDouble();
                visitItems.insert(startItem);
                break;
            case 2 :
                result += startItem->GetText().toDouble() * endItem->GetText().toDouble();
                visitItems.insert(endItem);
                break;
            case 3 :
                result += startItem->GetText().toDouble() / endItem->GetText().toDouble();
                visitItems.insert(endItem);
                break;
            default:
                result += startItem->GetText().toDouble() - endItem->GetText().toDouble();
                break;

            }
        }
    }
    emit resultUpdated(QString::number(result));
}

void CustomGraphicsView::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open file for writing");
        return;
    }

    QDataStream out(&file);

    // Save all CustomPixmapItems
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (CustomPixmapItem *pixmapItem = dynamic_cast<CustomPixmapItem *>(item)) {
            out << QString("CustomPixmapItem");
            pixmapItem->write(out);
        } else if (ArrowLineItem *lineItem = dynamic_cast<ArrowLineItem *>(item)) {
            out << QString("ArrowLineItem");
            lineItem->write(out);
        }
    }

    QMessageBox msgBox;
    msgBox.setText("Data Saved Succesfully!!!");
    msgBox.exec();


}

void CustomGraphicsView::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file for reading");
        return;
    }

    QDataStream in(&file);

    scene->clear();
    lineConnections.clear();

    QList<ArrowLineItem*> lineItems;
    QMap<int, CustomPixmapItem*> customItems;
    while (!in.atEnd()) {
        QString itemType;
        in >> itemType;

        if (itemType == "CustomPixmapItem") {
            CustomPixmapItem *pixmapItem = new CustomPixmapItem(QPixmap());
            pixmapItem->read(in);
            pixmapItem->HideLabelIfNeeded();
            scene->addItem(pixmapItem);
            customItems.insert(pixmapItem->GetItemId(), pixmapItem);
            connect(pixmapItem, &CustomPixmapItem::positionChanged, this, &CustomGraphicsView::updateLinePosition);
        } else if (itemType == "ArrowLineItem") {
            ArrowLineItem *lineItem = new ArrowLineItem(QLineF());
            lineItem->read(in);
            scene->addItem(lineItem);
            lineItems.append(lineItem);
        }

    }

    reconnectLines(lineItems, customItems);
}

void CustomGraphicsView::saveToXml(const QString &fileName)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("Scene");
    doc.appendChild(root);

    QList<QGraphicsItem *> items = scene->items();

    for (QGraphicsItem *item : items)
    {
        QDomElement element;

        if (auto pixmapItem = dynamic_cast<CustomPixmapItem *>(item))
        {
            element = doc.createElement("CustomPixmapItem");
            element.setAttribute("id", pixmapItem->GetItemId());
            element.setAttribute("x", pixmapItem->pos().x());
            element.setAttribute("y", pixmapItem->pos().y());

            // Save pixmap width and height
            QPixmap pixmap = pixmapItem->PixmapLabel->pixmap()->scaled(pixmapItem->pixmapWidth(), pixmapItem->pixmapHeight());
            element.setAttribute("width", pixmap.width());
            element.setAttribute("height", pixmap.height());

            // Save text
            element.setAttribute("text", pixmapItem->TextLabel->text());

            // Save pixmap data
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pixmap.save(&buffer, "PNG"); // Save pixmap to PNG format
            buffer.close();
            element.setAttribute("pixmapData", QString(byteArray.toBase64()));

            root.appendChild(element);
        }
        else if (auto lineItem = dynamic_cast<ArrowLineItem *>(item))
        {
            element = doc.createElement("ArrowLineItem");
            element.setAttribute("startX", lineItem->line().x1());
            element.setAttribute("startY", lineItem->line().y1());
            element.setAttribute("endX", lineItem->line().x2());
            element.setAttribute("endY", lineItem->line().y2());
            root.appendChild(element);
        }
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Could not open file for writing";
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    QMessageBox msgBox;
    msgBox.setText("Data in Xml Saved Successfully!");
    msgBox.exec();
}

void CustomGraphicsView::loadFromXml(const QString &fileName)
{
    QDomDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Could not open file for reading";
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        qWarning() << "Failed to parse XML";
        return;
    }

    QDomElement root = doc.documentElement();
    QDomNodeList pixmapNodes = root.elementsByTagName("CustomPixmapItem");
    QDomNodeList lineNodes = root.elementsByTagName("ArrowLineItem");

    // Clear existing scene and connections
    scene->clear();
    lineConnections.clear();

    QMap<int, CustomPixmapItem*> customItems;
    QList<ArrowLineItem*> lineItems;

    // Load pixmap items
    for (int i = 0; i < pixmapNodes.count(); i++)
    {
        QDomElement element = pixmapNodes.at(i).toElement();
        CustomPixmapItem *pixmapItem = new CustomPixmapItem(QPixmap());

        // Set position
        pixmapItem->setPos(element.attribute("x").toDouble(), element.attribute("y").toDouble());

        // Load pixmap data
        QByteArray byteArray = QByteArray::fromBase64(element.attribute("pixmapData").toUtf8());
        QPixmap pixmap;
        if (!pixmap.loadFromData(byteArray, "PNG"))
        {
            qWarning() << "Failed to load pixmap from data for item with ID:" << element.attribute("id");
            delete pixmapItem; // Clean up the item
            continue;
        }
        pixmapItem->PixmapLabel = new QLabel();
        pixmapItem->PixmapLabel->setPixmap(pixmap);

        // Set text and item ID
        pixmapItem->SetText(element.attribute("text"));
        pixmapItem->SetItemId(element.attribute("id").toInt());

        scene->addItem(pixmapItem);
        customItems.insert(pixmapItem->GetItemId(), pixmapItem);
        connect(pixmapItem, &CustomPixmapItem::positionChanged, this, &CustomGraphicsView::updateLinePosition);
    }

    // Load line items
    for (int i = 0; i < lineNodes.count(); i++)
    {
        QDomElement element = lineNodes.at(i).toElement();
        ArrowLineItem *lineItem = new ArrowLineItem(QLineF(
                                                        QPointF(element.attribute("startX").toDouble(), element.attribute("startY").toDouble()),
                                                        QPointF(element.attribute("endX").toDouble(), element.attribute("endY").toDouble())
                                                        ));

        scene->addItem(lineItem);
        lineItems.append(lineItem);
    }

    // Reconnect lines after all items are loaded
    reconnectLines(lineItems, customItems);
}



void CustomGraphicsView::reconnectLines(QList<ArrowLineItem*> lineItems, QMap<int, CustomPixmapItem*> customItems)
{
    for (ArrowLineItem* line : lineItems) {
        if(line->GetIsStartCircleStartConnected())
        {
            line->SetStartCircle(customItems[line->GetStartCircleItemId()]->GetStartCircle());
        }

        if(line->GetIsStartCircleEndConnected())
        {
            line->SetStartCircle(customItems[line->GetStartCircleItemId()]->GetEndCircle());
        }

        if(line->GetIsEndCircleStartConnected())
        {
            line->SetEndCircle(customItems[line->GetEndCircleItemId()]->GetStartCircle());
        }

        if(line->GetIsEndCircleEndConnected())
        {
            line->SetEndCircle(customItems[line->GetEndCircleItemId()]->GetEndCircle());
        }

        if (line->GetStartCircle() && line->GetEndCircle()) {
            lineConnections[line].first = line->GetStartCircle();
            lineConnections[line].second = line->GetEndCircle();
        }
    }
    updateLinePosition();
}

void CustomGraphicsView::EmitDebugData(QPoint pos)
{
    emit PublishUndoData(QString());
    emit PublishRedoData(QString());
    emit PublishNewData(QString());
    emit PublishOldData(QString());
    emit PublishOldData(QString("(%1, %2)").arg(mapToScene(pos).x()).arg(mapToScene(pos).y()));
}

void CustomGraphicsView::AddItemToAddStack(QGraphicsItem* item)
{
    AddCommand* command = new AddCommand(scene, item);
    connect(command, &AddCommand::PublishUndoData, this, &CustomGraphicsView::PublishUndoData);
    connect(command, &AddCommand::PublishRedoData, this, &CustomGraphicsView::PublishRedoData);
    connect(command, &AddCommand::NotifyUndoCompleted, this, &CustomGraphicsView::updateLinePosition);
    connect(command, &AddCommand::NotifyRedoCompleted, this, &CustomGraphicsView::updateLinePosition);
    UndoStack->push(command);
}

void CustomGraphicsView::AddItemToMoveStack(QGraphicsItem* item)
{
    MoveCommand* command = new MoveCommand(item, itemStartPosition, item->scenePos());
    connect(command, &MoveCommand::PublishUndoData, this, &CustomGraphicsView::PublishUndoData);
    connect(command, &MoveCommand::PublishRedoData, this, &CustomGraphicsView::PublishRedoData);

    connect(command, &MoveCommand::NotifyUndoCompleted, this, &CustomGraphicsView::updateLinePosition);
    connect(command, &MoveCommand::NotifyRedoCompleted, this, &CustomGraphicsView::updateLinePosition);

    UndoStack->push(command);
}
