#include <addcommand.h>

AddCommand::AddCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent)
    : QUndoCommand(parent), GScene(scene), Item(item)
{

}

void AddCommand::undo()
{
    GScene->removeItem(Item);
}

void AddCommand::redo()
{
    GScene->addItem(Item);
}

RemoveCommand::RemoveCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent)
        : QUndoCommand(parent), GScene(scene), Item(item)
{

}

void RemoveCommand::undo()
{
    GScene->addItem(Item);
}

void RemoveCommand::redo()
{
    GScene->removeItem(Item);
}

MoveCommand::MoveCommand(QGraphicsItem* item, const QPointF& oldPos, const QPointF& newPos, QUndoCommand* parent)
    : QUndoCommand(parent), Item(item), OldPos(oldPos), NewPos(newPos)
{

}

void MoveCommand::undo()
{
    Item->setPos(OldPos);
}

void MoveCommand::redo()
{
    Item->setPos(NewPos);
}
