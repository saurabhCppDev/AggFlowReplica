#include "customgraphicsview.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <arrowlineitem.h>
#include <QIcon>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QMessageBox>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), currentLine(nullptr)
{
    setScene(scene);
    setAcceptDrops(true);

    scene->setSceneRect(0, 0,600,400);

    acnSave = new QAction(tr("Save Not Yet Implemented"), this);
    acnDel = new QAction(tr("Delete line"), this);

    connect(acnSave, &QAction::triggered, this, &CustomGraphicsView::onActionSave);
    connect(acnDel, &QAction::triggered, this, &CustomGraphicsView::onActionDelete);
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
        QString name = roleDataMap[Qt::DisplayRole].toString();
        QPixmap pixmap = icon.pixmap(64, 64);

        CustomPixmapItem* item = new CustomPixmapItem(pixmap, name);
        item->setPos(mapToScene(event->pos()));
        scene->addItem(item);

        connect(item, &CustomPixmapItem::positionChanged, this, &CustomGraphicsView::updateLinePosition);
        connect(item, &CustomPixmapItem::valueChanged, this, &CustomGraphicsView::handleValueChanged);

        event->acceptProposedAction();
    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
        QList<QGraphicsItem *> items = scene->items(scenePos);

        for (auto item : items)
        {
            if (auto startEllipse = dynamic_cast<QGraphicsEllipseItem *>(item))
            {
                lineStartPoint = startEllipse->scenePos();
                currentLine = new ArrowLineItem(QLineF(lineStartPoint, lineStartPoint));
                scene->addItem(currentLine);
                lineConnections[currentLine] = qMakePair(startEllipse, nullptr);
                break;
            }
        }
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

    QGraphicsView::mouseMoveEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (currentLine)
    {
        QPointF scenePos = mapToScene(event->pos());
        QList<QGraphicsItem *> items = scene->items(scenePos);

        bool lineDrawn = false;
        for (auto item : items)
        {
            if (auto endEllipse = dynamic_cast<QGraphicsEllipseItem *>(item))
            {
                QLineF finalLine(lineStartPoint, endEllipse->scenePos());
                currentLine->setLine(finalLine);
                lineConnections[currentLine].second = endEllipse;
                lineDrawn = true;

                // Print names of the connected items
                CustomPixmapItem *startItem = dynamic_cast<CustomPixmapItem *>(lineConnections[currentLine].first->parentItem());
                CustomPixmapItem *endItem = dynamic_cast<CustomPixmapItem *>(endEllipse->parentItem());

                if (startItem && endItem)
                {
                    qDebug() << "Connected:" << startItem->getName() << "and" << endItem->getName();
                }
                break;
            }
        }

        if (!lineDrawn)
        {
            scene->removeItem(currentLine);
            delete currentLine;
        }

        currentLine = nullptr;
    }

    QGraphicsView::mouseReleaseEvent(event);
}


void CustomGraphicsView::updateLinePosition()
{
    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
    {
        ArrowLineItem *line = it.key(); // Ensure this is of type ArrowLineItem*
        QGraphicsEllipseItem *startEllipse = it.value().first;
        QGraphicsEllipseItem *endEllipse = it.value().second;

        if (startEllipse && endEllipse)
        {
            line->setLine(QLineF(startEllipse->scenePos(), endEllipse->scenePos()));

            // Debug: Print names of the connected items
            CustomPixmapItem *startItem = dynamic_cast<CustomPixmapItem *>(startEllipse->parentItem());
            CustomPixmapItem *endItem = dynamic_cast<CustomPixmapItem *>(endEllipse->parentItem());

            if (startItem && endItem)
            {
                qDebug() << "Line updated between:" << startItem->getName() << "and" << endItem->getName();
            }
        }
    }
}



void CustomGraphicsView::ClearScene()
{
    scene->clear();
}


void CustomGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    ArrowLineItem *item = dynamic_cast<ArrowLineItem *>(itemAt(event->pos()));
    if (item)
    {
        // Add actions to the context menu
        contextMenu.addAction(acnSave);
        contextMenu.addAction(acnDel);
        itemToDelete = item;
        // Show the context menu at the cursor position
        contextMenu.exec(event->globalPos());
    }
}

void CustomGraphicsView::handleValueChanged(double value)
{
    double result = calculateConnectedItems();
    qDebug() << "Connected items: " << result;
    qDebug() << "Input Value "<< value;
}


double CustomGraphicsView::calculateConnectedItems() const
{
    QSet<CustomPixmapItem *> visitedItems;
    double sum = 0.0;

    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
    {
        QGraphicsEllipseItem *startEllipse = it.value().first;
        QGraphicsEllipseItem *endEllipse = it.value().second;

        if (startEllipse && endEllipse)
        {
            CustomPixmapItem *startItem = dynamic_cast<CustomPixmapItem *>(startEllipse->parentItem());
            CustomPixmapItem *endItem = dynamic_cast<CustomPixmapItem *>(endEllipse->parentItem());

            if (startItem && !visitedItems.contains(startItem))
            {
                sum += startItem->getValue();
                visitedItems.insert(startItem);
            }
            if (endItem && !visitedItems.contains(endItem))
            {
                sum += endItem->getValue();
                visitedItems.insert(endItem);
            }
            qDebug() << "Item with name" << startItem->getName() << "is connected to item with name" << endItem->getName();
        }
    }

    return sum;
}

void CustomGraphicsView::onActionSave()
{
    // Action 1 triggered

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Save File", "Do you want to save the file?",
                                     QMessageBox::Yes | QMessageBox::No);

       if (reply == QMessageBox::No)
       {
           return;
       }

       QFile file("scene_data.xml");
       if (!file.open(QIODevice::WriteOnly))
       {
           QMessageBox::critical(this, "Save Error", "Cannot open file for writing:\n" + file.errorString());
           return;
       }

       QXmlStreamWriter xmlWriter(&file);
       xmlWriter.setAutoFormatting(true);
       xmlWriter.writeStartDocument();
       xmlWriter.writeStartElement("Scene");

       // Write items
       xmlWriter.writeStartElement("Items");
       foreach (QGraphicsItem *item, scene->items())
       {
           CustomPixmapItem *pixmapItem = dynamic_cast<CustomPixmapItem *>(item);
           if (pixmapItem)
           {
               xmlWriter.writeStartElement("Item");
               xmlWriter.writeAttribute("type", "Pixmap");
               xmlWriter.writeAttribute("name", pixmapItem->getName());
               xmlWriter.writeAttribute("value", QString::number(pixmapItem->getValue()));
               xmlWriter.writeAttribute("x", QString::number(pixmapItem->x()));
               xmlWriter.writeAttribute("y", QString::number(pixmapItem->y()));

               xmlWriter.writeStartElement("ConnectionPoints");
               foreach (QGraphicsEllipseItem *ellipse, pixmapItem->getConnectionPoints())
               {
                   xmlWriter.writeStartElement("Point");
                   xmlWriter.writeAttribute("x", QString::number(ellipse->x()));
                   xmlWriter.writeAttribute("y", QString::number(ellipse->y()));
                   xmlWriter.writeEndElement();
               }
               xmlWriter.writeEndElement(); // ConnectionPoints

               xmlWriter.writeEndElement(); // Item
           }
       }
       xmlWriter.writeEndElement(); // Items

       // Write connections
       xmlWriter.writeStartElement("Connections");
       for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
       {
           QGraphicsLineItem *line = it.key();
           QGraphicsEllipseItem *startEllipse = it.value().first;
           QGraphicsEllipseItem *endEllipse = it.value().second;

           if (startEllipse && endEllipse)
           {
               CustomPixmapItem *startItem = dynamic_cast<CustomPixmapItem *>(startEllipse->parentItem());
               CustomPixmapItem *endItem = dynamic_cast<CustomPixmapItem *>(endEllipse->parentItem());

               if (startItem && endItem)
               {
                   xmlWriter.writeStartElement("Connection");
                   xmlWriter.writeAttribute("startItem", startItem->getName());
                   xmlWriter.writeAttribute("endItem", endItem->getName());
                   xmlWriter.writeEndElement(); // Connection
               }
           }
       }
       xmlWriter.writeEndElement(); // Connections

       xmlWriter.writeEndElement(); // Scene
       xmlWriter.writeEndDocument();

       file.close();
       QMessageBox::information(this, "Save Success", "File saved successfully!");
}


//remove lines and break connections . Remember to delete pointers
void CustomGraphicsView::RemoveLines()
{
    ArrowLineItem * arrowLine = dynamic_cast<ArrowLineItem *>(itemToDelete);
    //    LineConnectionsMap::iterator itr = lineConnections.find(arrowLine);
    //    delete itr->first;
    //    delete itr->second;
    if(arrowLine)
        lineConnections.remove(arrowLine);
}

void CustomGraphicsView::onActionDelete()
{
    if (itemToDelete)
    {
        scene->removeItem(itemToDelete);
        RemoveLines();
        delete itemToDelete;
        itemToDelete = nullptr;
    }
}

QList<QPair<QString, QString>> CustomGraphicsView::getConnections() const
{
    QList<QPair<QString, QString>> connections;
    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it)
    {
        QGraphicsEllipseItem *startEllipse = it.value().first;
        QGraphicsEllipseItem *endEllipse = it.value().second;

        if (startEllipse && endEllipse)
        {
            CustomPixmapItem *startItem = dynamic_cast<CustomPixmapItem *>(startEllipse->parentItem());
            CustomPixmapItem *endItem = dynamic_cast<CustomPixmapItem *>(endEllipse->parentItem());

            if (startItem && endItem)
            {
                connections.append(qMakePair(startItem->getName(), endItem->getName()));
            }
        }
    }
    return connections;
}

