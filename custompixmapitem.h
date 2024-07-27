#ifndef CUSTOMPIXMAPITEM_H
#define CUSTOMPIXMAPITEM_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QLabel>

class CustomPixmapItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    static int id;
    CustomPixmapItem(const QPixmap &pixmap);
    void SetText(const QString &text);
    void write(QDataStream &out) const;
    void read(QDataStream &in);
    void SetStartConnected(bool connected);
    void SetEndConnected(bool connected);

signals:
    void positionChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    void AddEndCircles();

    QPointF dragStartPosition;
    bool dragging;
    QWidget * container;
    QLabel* lbl;
    QLabel* pixmapLabel;
    QGraphicsProxyWidget* proxyWid;
    QGraphicsEllipseItem *startCircle;
    QGraphicsEllipseItem *endCircle;
    bool startC;
    bool endC;
};

#endif // CUSTOMPIXMAPITEM_H
