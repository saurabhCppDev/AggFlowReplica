#ifndef ARROWLINEITEM_H
#define ARROWLINEITEM_H

#include <QGraphicsLineItem>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <cmath>

class ArrowLineItem : public QGraphicsLineItem
{
public:
    ArrowLineItem(QLineF line, QGraphicsItem* parent = nullptr);
    int lineWidth;
    void write(QDataStream &out) const;
    void read(QDataStream &in);

public:
    void SetStartCircle(QGraphicsEllipseItem* circle);
    void SetEndCircle(QGraphicsEllipseItem* circle);

    QGraphicsEllipseItem* GetStartCircle();
    QGraphicsEllipseItem* GetEndCircle();

private:
    QGraphicsEllipseItem* startCircle;
    QGraphicsEllipseItem* endCircle;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // ARROWLINEITEM_H
