#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPointF>

class AddCommand : public QUndoCommand {
public:
    AddCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent = nullptr);

protected:
    void undo() override;
    void redo() override;

private:
    QGraphicsScene* GScene;
    QGraphicsItem* Item;
};

class RemoveCommand : public QUndoCommand {
public:
    RemoveCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent = nullptr);

protected:
    void undo() override;
    void redo() override;

private:
    QGraphicsScene* GScene;
    QGraphicsItem* Item;
};

class MoveCommand : public QUndoCommand {
public:
    MoveCommand(QGraphicsItem* item, const QPointF& oldPos, const QPointF& newPos, QUndoCommand* parent = nullptr);

protected:
    void undo() override;
    void redo() override;

private:
    QGraphicsItem* Item;
    QPointF OldPos;
    QPointF NewPos;
};

#endif // ADDCOMMAND_H
