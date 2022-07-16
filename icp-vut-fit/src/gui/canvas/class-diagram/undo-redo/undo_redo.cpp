#include "src/gui/canvas/class-diagram/undo-redo/undo_redo.h"
#include <utility>

Cmd_add_entity::Cmd_add_entity(QGraphicsScene *scene_, Entity *entity_,
                               QUndoCommand *parent)
        : QUndoCommand(parent), scene(scene_), entity(entity_) {
    setText("add");
}

Cmd_add_entity::~Cmd_add_entity() = default;

void Cmd_add_entity::undo() {
    for (auto &child: entity->childItems()) {
        if (Class_diagram::is_relation_point(child)) {
            Relation_line *line = ((Relation_point *) child)->line;
            line->delete_points();
            delete line;
        }
    }
    delete entity;
    QUndoCommand::undo();
}

void Cmd_add_entity::redo() {
    QUndoCommand::redo();
}

Cmd_move_entity::Cmd_move_entity(QGraphicsScene *scene_, Entity *entity_)
        : scene(scene_), entity(entity_), last_pos(entity_->pos()) {
    setText("move");
}

void Cmd_move_entity::undo() {
    entity->setPos(last_pos);
    QUndoCommand::undo();
}

void Cmd_move_entity::redo() {
    QUndoCommand::redo();
}

Cmd_move_entity::~Cmd_move_entity() = default;

Cmd_delete_entity::Cmd_delete_entity(QGraphicsScene *scene_,
                                     Entity *entity_) :
        scene(scene_), entity(entity_) {
    setText("delete");
}

Cmd_delete_entity::~Cmd_delete_entity() = default;

void Cmd_delete_entity::undo() {
    entity->show();
    for (auto &child: entity->childItems()) {
        if (Class_diagram::is_relation_point(child)) {
            Relation_line *line = ((Relation_point *) child)->line;
            line->delete_points();
            line->show();
        }
    }
    QUndoCommand::undo();
}

void Cmd_delete_entity::redo() {
    QUndoCommand::redo();
}

Cmd_text_changed_entity::Cmd_text_changed_entity(Entity_text *entity_text_, QString str)
        : entity_text(entity_text_), last_text(std::move(str)) {}

Cmd_text_changed_entity::~Cmd_text_changed_entity() = default;

void Cmd_text_changed_entity::undo() {
    entity_text->setPlainText(last_text);
    QUndoCommand::undo();
}

void Cmd_text_changed_entity::redo() {
    QUndoCommand::redo();
}



