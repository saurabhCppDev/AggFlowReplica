#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QMap>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include "custompixmapitem.h"
#include <arrowlineitem.h>


//using LineConnectionsMap = QMap<QGraphicsLineItem *, QPair<QGraphicsEllipseItem *, QGraphicsEllipseItem *>>;
using LineConnectionsMap = QMap<ArrowLineItem *, QPair<QGraphicsEllipseItem *, QGraphicsEllipseItem *>>;

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomGraphicsView(QWidget *parent = nullptr);
    void ClearScene();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void updateLinePosition();
    void handleValueChanged(double value);
    void onActionSave();
    void onActionDelete();

private:
    void RemoveLines();
    double calculateConnectedItems() const;

    QList<QPair<QString, QString>> getConnections() const;

    QGraphicsScene *scene;
    ArrowLineItem *currentLine;
    QPointF lineStartPoint;
    LineConnectionsMap lineConnections;
    QAction *acnSave;
    QAction *acnDel;
    QMenu contextMenu;
    QGraphicsItem *itemToDelete = nullptr;

};

#endif // CUSTOMGRAPHICSVIEW_H
