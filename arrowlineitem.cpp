#include "ArrowLineItem.h"
#include <custompixmapitem.h>
#include <QColor>

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

void ArrowLineItem::write(QDataStream &out) const {
    out << line();
    out << dynamic_cast<CustomPixmapItem *>(StartCircle->parentItem())->GetItemId();
    out << dynamic_cast<CustomPixmapItem *>(StartCircle->parentItem())->GetStartConnected();
    out << dynamic_cast<CustomPixmapItem *>(StartCircle->parentItem())->GetEndConnected();

    out << dynamic_cast<CustomPixmapItem *>(EndCircle->parentItem())->GetItemId();
    out << dynamic_cast<CustomPixmapItem *>(EndCircle->parentItem())->GetStartConnected();
    out << dynamic_cast<CustomPixmapItem *>(EndCircle->parentItem())->GetEndConnected();
}

void ArrowLineItem::read(QDataStream &in) {
    QLineF line;
    in >> line;
    setLine(line);

    int itemIdStart, itemIdEnd;
    bool startCircleStartItem, EndCircleStartItem, startCircleEndItem, EndCircleEndItem;
    in >> itemIdStart >> startCircleStartItem >> EndCircleStartItem >> itemIdEnd >> startCircleEndItem >> EndCircleEndItem;

    StartCircleItemId = itemIdStart;
    IsStartCircleStartConnected = startCircleStartItem;
    IsStartCircleEndConnected = EndCircleStartItem;
    EndCircleItemId = itemIdEnd;
    IsEndCircleStartConnected = startCircleEndItem;
    IsEndCircleEndConnected = EndCircleEndItem;
}

void ArrowLineItem::SetStartCircle(QGraphicsEllipseItem *circle)
{
    StartCircle = new QGraphicsEllipseItem;
    StartCircle = circle;
}

void ArrowLineItem::SetEndCircle(QGraphicsEllipseItem *circle)
{
    EndCircle = new QGraphicsEllipseItem;
    EndCircle = circle;
}

QGraphicsEllipseItem *ArrowLineItem::GetStartCircle()
{
    return StartCircle;
}

QGraphicsEllipseItem *ArrowLineItem::GetEndCircle()
{
    return EndCircle;
}

void ArrowLineItem::SetStartCircleAttributes()
{
    CustomPixmapItem *parentItem = dynamic_cast<CustomPixmapItem *>(StartCircle->parentItem());
    QColor clr = StartCircle->brush().color();
    clr == Qt::red ? parentItem->SetStartConnected(true) : parentItem->SetEndConnected(true);
}

void ArrowLineItem::SetEndCircleAttributes()
{
    CustomPixmapItem *parentItem = dynamic_cast<CustomPixmapItem *>(EndCircle->parentItem());
    QColor clr = EndCircle->brush().color();
    clr == Qt::red ? parentItem->SetStartConnected(true) : parentItem->SetEndConnected(true);
}

int ArrowLineItem::GetStartCircleItemId() const
{
    return StartCircleItemId;
}

int ArrowLineItem::GetEndCircleItemId() const
{
    return EndCircleItemId;
}

bool ArrowLineItem::GetIsStartCircleStartConnected() const
{
    return IsStartCircleStartConnected;
}

bool ArrowLineItem::GetIsStartCircleEndConnected() const
{
    return IsStartCircleEndConnected;
}

bool ArrowLineItem::GetIsEndCircleStartConnected() const
{
    return IsEndCircleStartConnected;
}

bool ArrowLineItem::GetIsEndCircleEndConnected() const
{
    return IsEndCircleEndConnected;
}
