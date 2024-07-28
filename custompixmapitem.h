#ifndef CUSTOMPIXMAPITEM_H
#define CUSTOMPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class CustomPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CustomPixmapItem(const QPixmap &pixmap, const QString &name, QGraphicsItem *parent = nullptr);

    QGraphicsEllipseItem* getConnectionPoint(const QPointF& point) const;
    QList<QGraphicsEllipseItem*> getConnectionPoints() const;

    double getValue() const { return value; }
    void setValue(double value) { this->value = value; }

    QString getName() const { return name; }
    void setName(const QString &name) { this->name = name; }

signals:
    void positionChanged();
    void valueChanged(double newValue);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

public:
    QGraphicsEllipseItem *startCircle;
    QGraphicsEllipseItem *endCircle;

private:
    void AddEndCircles(const QPixmap &pixmap);
    QList<QGraphicsEllipseItem*> connectionPoints;
    QString name;
    double value;
    bool dragging;
    QPointF dragStartPosition;
};

#endif // CUSTOMPIXMAPITEM_H
