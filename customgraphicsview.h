#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QMap>
#include "CustomPixmapItem.h"
#include <arrowlineitem.h>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

using LineConnectionsMap = QMap<QGraphicsLineItem *, QPair<QGraphicsEllipseItem *, QGraphicsEllipseItem *>>;

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
    void onActionSave();
    void onActionDelete();

private:
    void RemoveLines();

    QGraphicsScene *scene;
    ArrowLineItem *currentLine;
    QPointF lineStartPoint;
    LineConnectionsMap lineConnections;
    QMenu contextMenu;
    QAction *acnSave;
    QAction *acnDel;
    QGraphicsItem *itemToDelete = nullptr;
};

#endif // CUSTOMGRAPHICSVIEW_H
