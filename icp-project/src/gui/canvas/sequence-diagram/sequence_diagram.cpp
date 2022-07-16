/**
 * @author Andrej Bínovský (xbinov00)
 * @file sequence_diagram.cpp
 */

#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"

Sequence_diagram::Sequence_diagram(QGraphicsScene *scene) :
        scene(scene) {}

void Sequence_diagram::create_actor() {
    if (!Lifeline::size.contains(Input_entity::diagram_name)) {
        Lifeline::size[Input_entity::diagram_name] = 400;
    }
    auto actor = new Actor(0, 0, 30, "Name");
    actor->setData(10, Input_entity::diagram_name);
    scene->addItem(actor);
}

void Sequence_diagram::create_object() {
    if (!Lifeline::size.contains(Input_entity::diagram_name)) {
        Lifeline::size[Input_entity::diagram_name] = 400;
    }
    auto object = new Object_e(0, 0, 50, "Name");
    object->setData(10, Input_entity::diagram_name);
    scene->addItem(object);
}

void Sequence_diagram::create_box() {
    auto items = scene->selectedItems();
    if (!items.isEmpty() && items.first()->data(0) == "lifeline") {
        auto lifeline = (Lifeline *) items.first();
        auto box = new Box(0, 80, lifeline);
        box->setData(10, Input_entity::diagram_name);
    }
}

void Sequence_diagram::create_message(bool is_dashed, bool is_black_arrow, bool is_created) {
    QGraphicsRectItem *entity_from = nullptr;
    QGraphicsRectItem *entity_to = nullptr;
    Q_FOREACH(auto entity, scene->items()) {
            if (Message::get_name((QGraphicsRectItem *) entity) == Input_entity::entity_from and
                !Input_entity::entity_from.isEmpty() and
                entity->data(10).toString() == Input_entity::diagram_name)
                entity_from = (QGraphicsRectItem *) entity;
            if (Message::get_name((QGraphicsRectItem *) entity) == Input_entity::entity_to and
                !Input_entity::entity_to.isEmpty() and
                entity->data(10).toString() == Input_entity::diagram_name)
                entity_to = (QGraphicsRectItem *) entity;
        }
    if (entity_from and entity_to and entity_from != entity_to) {
        auto message = new Message(entity_from, entity_to, 40, is_dashed, is_black_arrow, is_created, "message");
        message->setData(10, Input_entity::diagram_name);
        scene->addItem(message);
    }
}

void Sequence_diagram::create_message_sync() {
    create_message(false, true, false);
}

void Sequence_diagram::create_message_async() {
    create_message(false, false, false);
}

void Sequence_diagram::create_message_create() {
    create_message(true, false, true);
}

void Sequence_diagram::create_message_async_return() {
    create_message(true, false, false);
}

void Sequence_diagram::set_diagram() {
    if (input_diagram_name != nullptr) {
        auto items = scene->selectedItems();
        if (!items.empty()) {
            auto new_name = items.first()->data(10).toString();
            if (!new_name.isEmpty()) {
                Input_entity::diagram_name = new_name;
                input_diagram_name->input->setText(new_name);
            }

        }
    }
}

void Sequence_diagram::delete_items() {
    Q_FOREACH(auto item, scene->selectedItems()) {
            if (item->data(0) == "actor") {
                delete_children(((Actor *) item)->lifeline->childItems());
                delete_children(((Actor *) item)->childItems());
                delete item;
            }
            if (item->data(0) == "object") {
                delete_children(((Object_e *) item)->lifeline->childItems());
                delete_children(((Object_e *) item)->childItems());
                delete item;
            }
            if (item->data(0) == "point") {
                delete item;
            }
            if (item->data(0) == "box") {
                delete item;
            }
        }
}

void Sequence_diagram::delete_entities(QGraphicsScene *s, const QString &name) {
    Q_FOREACH(auto item, s->items()) {
            if (Message::get_name(item) == name) {
                if (item->data(0) == "actor") {
                    delete_children(((Actor *) item)->lifeline->childItems());
                    delete_children(((Actor *) item)->childItems());
                    delete item;
                }
                if (item->data(0) == "object") {
                    delete_children(((Object_e *) item)->lifeline->childItems());
                    delete_children(((Object_e *) item)->childItems());
                    delete item;
                }
            }
        }
}

void Sequence_diagram::delete_children(const QList<QGraphicsItem *> &children) {
    Q_FOREACH(auto child, children) {
            if (child->data(0) == "box" or child->data(0) == "point")
                delete child;
        }
}

void Sequence_diagram::change_entity_name(QGraphicsScene *s, const QString &old_string, const QString &new_string) {
    Q_FOREACH(auto entity, s->items()) {
            if (Message::get_name(entity) == old_string) {
                if (entity->data(0).toString() == "actor") {
                    ((Actor *) entity)->name->setPlainText(new_string);
                    ((Actor *) entity)->name->set_pos();
                }
                if (entity->data(0).toString() == "object") {
                    ((Object_e *) entity)->name->setPlainText(new_string);
                    ((Object_e *) entity)->name->set_pos();
                }
            }
        }
}

void Sequence_diagram::change_message_name(QGraphicsScene *s, const QString &old_string,
                                           const QString &new_string, const QString &entity_name) {
    Q_FOREACH(auto entity, s->items()) {
            if (entity->data(0).toString() == "message") {
                auto message = ((Message *) entity);
                if (message->name->toPlainText() == old_string and
                    Message::get_name(message->parent_to) == entity_name) {
                    ((Message *) entity)->name->setPlainText(new_string);
                    ((Message *) entity)->name->set_pos();
                }

            }
        }
}
