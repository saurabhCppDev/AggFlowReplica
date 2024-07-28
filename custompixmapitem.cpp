#include "custompixmapitem.h"
#include <QGraphicsScene>
#include <QPen>
#include <QDebug>
#include <QInputDialog>
#include <QMimeData>

CustomPixmapItem::CustomPixmapItem(const QPixmap &pixmap, const QString &name, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent), name(name), value(0.0), dragging(false)
{

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);

    AddEndCircles(pixmap);
}

QGraphicsEllipseItem* CustomPixmapItem::getConnectionPoint(const QPointF& point) const
{
    foreach (QGraphicsEllipseItem* ellipse, connectionPoints)
    {
        if (ellipse->boundingRect().contains(mapFromScene(point)))
        {
            return ellipse;
        }
    }
    return nullptr;
}

QList<QGraphicsEllipseItem*> CustomPixmapItem::getConnectionPoints() const
{
    return connectionPoints;
}

void CustomPixmapItem::AddEndCircles(const QPixmap &pixmap)
{
    // Create and position the circles opacity and colour i will adjust later
    startCircle = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    startCircle->setBrush(Qt::blue);
    startCircle->setPos(0, pixmap.height() / 2);

    endCircle = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    endCircle->setBrush(Qt::red);
    //    endCircle->setOpacity(0.5);
    endCircle->setPos(pixmap.width(), pixmap.height() / 2);
}

void CustomPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragStartPosition = event->pos();
        dragging = true;
    }

    QGraphicsPixmapItem::mousePressEvent(event);
}


void CustomPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging)
    {
        QPointF newPos = pos() + event->pos() - dragStartPosition;
        setPos(newPos);
        emit positionChanged();
    }
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void CustomPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

QVariant CustomPixmapItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ((change == ItemPositionChange || change == ItemSelectedChange
         || change == ItemPositionHasChanged) && scene())
    {
        emit positionChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}

void CustomPixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        bool ok;
        double inputValue = QInputDialog::getDouble(nullptr, "Enter Value", "Value:", value, 0, 10000, 2, &ok);
        if (ok)
        {
            setValue(inputValue);
            emit valueChanged(inputValue);
        }
    }

}

