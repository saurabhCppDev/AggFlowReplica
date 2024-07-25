#include "ArrowLineItem.h"

ArrowLineItem::ArrowLineItem(QLineF line, QGraphicsItem* parent)
    : QGraphicsLineItem(line, parent)
    , lineWidth(2)
{
    QPen pen(Qt::black, lineWidth, Qt::DotLine); // Set pen to dotted line
    setPen(pen);
}

void ArrowLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsLineItem::paint(painter, option, widget);

    QLineF line = this->line();
    double angle = std::atan2(-line.dy(), line.dx());

    // Define the arrowhead points
    QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * 10, cos(angle + M_PI / 3) * 10);
    QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * 10, cos(angle + M_PI - M_PI / 3) * 10);

    // Draw the arrowhead with a solid pen
    // comment below 2 lines for solid arrowhead
    // 3rd line is for colour of arrowhead
//    QPen arrowPen(Qt::black, lineWidth, Qt::SolidLine);
//    painter->setPen(arrowPen);
//    painter->setBrush(Qt::green); // Fill color for the arrowhead

    QPolygonF arrowHead;
    arrowHead << line.p2() << arrowP1 << arrowP2;
    painter->drawPolygon(arrowHead);
}
