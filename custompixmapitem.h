#ifndef CUSTOMPIXMAPITEM_H
#define CUSTOMPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class CustomPixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    CustomPixmapItem(const QPixmap &pixmap);

signals:
    void positionChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

public:
    QGraphicsEllipseItem *startCircle;
    QGraphicsEllipseItem *endCircle;

private:
    QPointF dragStartPosition;
    bool dragging;
};

#endif // CUSTOMPIXMAPITEM_H
