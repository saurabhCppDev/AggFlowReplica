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

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , currentLine(nullptr)
    , UndoStack(new QUndoStack(this))
    , currentZoomLevel(1.0)
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

void CustomGraphicsView::zoomIn()
{
    currentZoomLevel *= 1.2; // Increase the zoom level by 20%
    setTransform(QTransform::fromScale(currentZoomLevel, currentZoomLevel));
}

void CustomGraphicsView::zoomOut()
{
    currentZoomLevel /= 1.2; // Decrease the zoom level by 20%
    setTransform(QTransform::fromScale(currentZoomLevel, currentZoomLevel));
}

void CustomGraphicsView::zoomToNatural()
{
    currentZoomLevel = 1.0; // Reset the zoom level to natural (1:1)
    setTransform(QTransform::fromScale(currentZoomLevel, currentZoomLevel));
}

void CustomGraphicsView::zoomToFit()
{
    QRectF rect = scene->itemsBoundingRect(); // Get the bounding rect of all items in the scene
    if (!rect.isEmpty()) {
        fitInView(rect, Qt::KeepAspectRatio); // Fit the scene in the view
        currentZoomLevel = transform().m11(); // Update the current zoom level
    }
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
