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

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // ARROWLINEITEM_H
