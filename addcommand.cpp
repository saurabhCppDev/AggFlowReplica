#include <addcommand.h>

AddCommand::AddCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent)
    : QUndoCommand(parent), GScene(scene), Item(item)
{

}

void AddCommand::undo()
{
    emit PublishUndoData(QString("(%1, %2)").arg(Item->pos().x()).arg(Item->pos().y()));
    emit NotifyUndoCompleted();
    GScene->removeItem(Item);
}

void AddCommand::redo()
{
    emit PublishRedoData(QString("(%1, %2)").arg(Item->pos().x()).arg(Item->pos().y()));
    emit NotifyRedoCompleted();
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
    emit PublishUndoData(QString("(%1, %2)").arg(OldPos.x()).arg(OldPos.y()));
    emit NotifyUndoCompleted();
    Item->setPos(OldPos);
}

void MoveCommand::redo()
{
    emit PublishRedoData(QString("(%1, %2)").arg(NewPos.x()).arg(NewPos.y()));
    emit NotifyRedoCompleted();
    Item->setPos(NewPos);
}
