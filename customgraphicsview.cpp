#include "CustomGraphicsView.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <arrowlineitem.h>
#include <QIcon>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), currentLine(nullptr) {
    setScene(scene);
    setAcceptDrops(true);
    scene->setSceneRect(0, 0,600,400);
    acnSave = new QAction(tr("Save Not Yet Implemented"), this);
    acnDel = new QAction(tr("Delete line"), this);

    connect(acnSave, &QAction::triggered, this, &CustomGraphicsView::onActionSave);
    connect(acnDel, &QAction::triggered, this, &CustomGraphicsView::onActionDelete);
}

void CustomGraphicsView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        event->acceptProposedAction();
    }
}

void CustomGraphicsView::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        event->acceptProposedAction();
    }
}

void CustomGraphicsView::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
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

        event->acceptProposedAction();
    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event) {
    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem *item = scene->itemAt(scenePos, QTransform());

    if (item && dynamic_cast<QGraphicsEllipseItem *>(item)) {
        lineStartPoint = scenePos;
        currentLine = new ArrowLineItem(QLineF(lineStartPoint, lineStartPoint));
        scene->addItem(currentLine);
        lineConnections[currentLine].first = dynamic_cast<QGraphicsEllipseItem *>(item);
    }

    QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (currentLine) {
        QLineF newLine(lineStartPoint, mapToScene(event->pos()));
        currentLine->setLine(newLine);
    }

    QGraphicsView::mouseMoveEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (currentLine) {
        QPointF scenePos = mapToScene(event->pos());
        QList<QGraphicsItem *>items = scene->items(scenePos);

        bool lineDrawn = false;
        for(auto item:items) {
            auto test = dynamic_cast<QGraphicsEllipseItem *>(item);
            if (item && test) {
                QLineF newLine(lineStartPoint, scenePos);
                currentLine->setLine(newLine);
                lineConnections[currentLine].second = dynamic_cast<QGraphicsEllipseItem *>(item);
                lineDrawn = true;
                break;
            }
        }

        if(!lineDrawn) {
            scene->removeItem(currentLine);
            delete currentLine;
        }

        currentLine = nullptr;
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void CustomGraphicsView::updateLinePosition() {
    for (auto it = lineConnections.begin(); it != lineConnections.end(); ++it) {
        QGraphicsLineItem *line = it.key();
        QGraphicsEllipseItem *startCircle = it.value().first;
        QGraphicsEllipseItem *endCircle = it.value().second;

        if (startCircle && endCircle) {
            line->setLine(QLineF(startCircle->scenePos(), endCircle->scenePos()));
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

void CustomGraphicsView::onActionSave()
{
    // Action 1 triggered
}

//remove lines and break connections . Remember to delete pointers
void CustomGraphicsView::RemoveLines()
{
    ArrowLineItem * arrowLine = dynamic_cast<ArrowLineItem *>(itemToDelete);
    LineConnectionsMap::iterator itr = lineConnections.find(arrowLine);
    delete itr->first;
    delete itr->second;
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
