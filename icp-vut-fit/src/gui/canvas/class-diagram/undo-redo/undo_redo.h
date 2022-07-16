#ifndef CLASS_DIAGRAM_UNDO_REDO_H
#define CLASS_DIAGRAM_UNDO_REDO_H

#include <QGraphicsTextItem>
#include "src/gui/canvas/class-diagram/entity/entity.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"
#include "src/gui/canvas/class-diagram/relation/relation_line.h"
#include "src/gui/canvas/class-diagram/entity/entity-text/entity_text.h"


class Cmd_add_entity : public QUndoCommand {
public:
    QGraphicsScene *scene;
    Entity *entity;

    Cmd_add_entity(QGraphicsScene *scene_, Entity *entity_, QUndoCommand *parent);

    ~Cmd_add_entity();

    void undo() override;

    void redo() override;
};

class Cmd_move_entity : public QUndoCommand {
public:
    QGraphicsScene *scene;
    Entity *entity;
    QPointF last_pos;

    Cmd_move_entity(QGraphicsScene *scene_, Entity *entity_);

    ~Cmd_move_entity();

    void undo() override;

    void redo() override;
};

class Cmd_delete_entity : public QUndoCommand {
public:
    QGraphicsScene *scene;
    Entity *entity;

    Cmd_delete_entity(QGraphicsScene *scene_, Entity *entity_);

    ~Cmd_delete_entity();

    void undo() override;

    void redo() override;
};

class Cmd_text_changed_entity : public QUndoCommand {
public:
    Cmd_text_changed_entity(Entity_text *pText, QString str);

    Entity_text *entity_text;
    const QString last_text;


    ~Cmd_text_changed_entity();

    void undo() override;

    void redo() override;
};

#endif // CLASS_DIAGRAM_UNDO_REDO_H
