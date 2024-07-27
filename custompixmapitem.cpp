#include "CustomPixmapItem.h"
#include <QGraphicsScene>
#include <QPen>
#include <QWidget>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>

int CustomPixmapItem::id = 0;

CustomPixmapItem::CustomPixmapItem(const QPixmap &pixmap)
    : dragging(false)
    , container(new QWidget)
    , lbl(new QLabel("Text"))
    , pixmapLabel(new QLabel)
    , proxyWid(new QGraphicsProxyWidget)
    , startCircle (new QGraphicsEllipseItem(-10, -10, 10, 10, this))
    , endCircle (new QGraphicsEllipseItem(-10, -10, 10, 10, this))
    , startC(false)
    , endC(false)
{
    setFlag(ItemIsMovable);
//    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);

    pixmapLabel->setPixmap(pixmap);
    AddEndCircles();
}

void CustomPixmapItem::AddEndCircles()
{
////  this way also we can add widget also depending on future requirement might need it so keeping commented code
//    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
//    pixmapItem->setPos(0, 0); // Position the image in the scene

    // Create a QGraphicsTextItem for displaying text
//    textItem->setDefaultTextColor(Qt::black); // Set text color
//    textItem->setFont(QFont("Arial", 16));    // Set text font and size
//    textItem->setPos(0, 55); // Position the text in the scene

    startCircle->setBrush(Qt::red);
    endCircle->setBrush(Qt::blue);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(lbl);
    layout->addWidget(pixmapLabel);
    container->setLayout(layout);
    container->setFixedSize(100,100);
    container->setAttribute(Qt::WA_TranslucentBackground);
    proxyWid->setWidget(container);
    lbl->setFont(QFont("Arial", 16));
    lbl->hide();

    addToGroup(proxyWid);
    addToGroup(startCircle);
    addToGroup(endCircle);

    // Update circle positions relative to the group
    QRectF bdRect = boundingRect();
    startCircle->setPos(-endCircle->boundingRect().width(), bdRect.height() / 2);
    endCircle->setPos(bdRect.width(), bdRect.height() / 2);

//    the circles opacity and colour i will adjust later if needed
//    endCircle->setOpacity(0.5);
}

void CustomPixmapItem::SetText(const QString &text)
{
    lbl->setText(text);
    lbl->show();
}

void CustomPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragStartPosition = event->pos();
        dragging = true;
    }
    QGraphicsItemGroup::mousePressEvent(event);
}

void CustomPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging)
    {
        QPointF newPos = pos() + event->pos() - dragStartPosition;
        setPos(newPos);
        emit positionChanged();
    }
    update();
    QGraphicsItemGroup::mouseMoveEvent(event);
}

void CustomPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
    }
    QGraphicsItemGroup::mouseReleaseEvent(event);
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

void CustomPixmapItem::write(QDataStream &out) const {
    out << pos();
    out << pixmapLabel->pixmap()->toImage();
    out << lbl->text();
}

void CustomPixmapItem::read(QDataStream &in) {
    QPointF position;
    QImage image;
    QString text;

    in >> position >> image >> text;

    setPos(position);
    pixmapLabel->setPixmap(QPixmap::fromImage(image));
    SetText(text);
}

void CustomPixmapItem::SetStartConnected(bool connected)
{

}

void CustomPixmapItem::SetEndConnected(bool connected)
{

}
