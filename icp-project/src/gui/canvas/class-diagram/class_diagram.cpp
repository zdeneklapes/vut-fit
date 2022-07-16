/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file class_diagram.cpp
 */

#include "src/gui/canvas/class-diagram/class_diagram.h"
#include "src/gui/side-toolbox/side_toolbox.h" // forward

Class_diagram::Class_diagram(QGraphicsScene *scene, Side_toolbox *side_toolbox_)
        : QObject(scene), scene(scene), side_toolbox(side_toolbox_) {}

Class_diagram::~Class_diagram() = default;

void Class_diagram::add_class() {
    const auto entity = new Entity(scene);
    Window::stack->push(new Cmd_add_entity(scene, entity, nullptr));
    scene->addItem(entity);
}

void Class_diagram::delete_class() {
    for (const QGraphicsItem *item: scene->selectedItems()) {
        if (Class_diagram::is_entity(item)) {
            Window::stack->push(new Cmd_delete_entity(scene, (Entity *) item));
            Sequence_diagram::delete_entities(scene, ((Entity *) item)->class_info->name);
            // relation lines
            for (auto &child: item->childItems()) {
                if (Class_diagram::is_relation_point(child)) {
                    Relation_line *line = ((Relation_point *) child)->line;
                    line->delete_points();
                    line->hide();
                }
            }
            ((Entity *) item)->hide();
        }
    }
}

bool Class_diagram::is_relation_point(const QGraphicsItem *item) {
    return item->data(0).toString() == "relation_point";
}

bool Class_diagram::is_entity(const QGraphicsItem *item) {
    return item->data(0).toString() == "entity";
}

bool Class_diagram::is_text_item(const QGraphicsItem *item) {
    return item->data(0).toString() == "entity_text";
}

Entity *Class_diagram::get_entity_from_child() {
    for (const QGraphicsItem *item: scene->selectedItems()) {
        if (Class_diagram::is_text_item(item)) {
            return (Entity *) item->parentItem();
        }
    }
    return nullptr;
}


void Class_diagram::run_selected(
        const std::function<bool(Entity_text *child_, const int idx, Entity *entity)> &cb_cond,
        const std::function<void(Entity_text *child_, const int idx, Entity *entity)> &cb_func) {
    Entity *entity = nullptr;
    if (!(entity = get_entity_from_child())) { return; }

    auto list = entity->get_text_item_child(entity);
    for (int i = 0; i < list->count(); ++i) {
        auto *child_ = (Entity_text *) (*list)[i];
        if (cb_cond(child_, i, entity)) {
            cb_func(child_, i, entity);
            delete list;
            return; // here because sig_sev when not
        }
    }
}

void Class_diagram::add_attribute() {
    run_selected(
            [=](Entity_text *child_, const int idx, Entity *entity) -> bool {
                return child_->isSelected() && idx - 1 < entity->class_info->attributes.count();
            },
            [=](Entity_text *child_, const int idx, Entity *entity) -> void {
                if (child_->isSelected() && idx - 1 < entity->class_info->attributes.count()) {
                    entity->class_info->insert_new_attribute(idx);
                    entity->update_elements();
                }
            });
}


void Class_diagram::delete_attribute() {
    run_selected(
            [=](const auto child_, const auto idx, const auto entity) -> bool {
                return child_->isSelected() && idx - 1 < entity->class_info->attributes.count();
            },
            [=](auto *child_, const auto idx, auto *entity) -> void {
                if (child_->isSelected() && idx - 1 < entity->class_info->attributes.count()) {
                    entity->class_info->remove_attribute(idx - 1);
                    entity->update_elements();
                }
            });
}

void Class_diagram::add_method() {
    run_selected(
            [=](const auto child_, const auto idx, const auto entity) -> bool {
                return child_->isSelected() && idx >= entity->class_info->attributes.count();
            },
            [=](auto *child_, const auto idx, auto *entity) -> void {
                if (child_->isSelected() && idx >= entity->class_info->attributes.count()) {
                    entity->class_info->insert_new_method(
                            idx - entity->class_info->attributes.count()
                    );
                    entity->update_elements();
                }
            });
}

void Class_diagram::delete_method() {
    run_selected(
            [=](const auto child_, const auto idx, const auto entity) -> bool {
                return child_->isSelected() && idx >= entity->class_info->attributes.count();
            },
            [=](auto *child_, const auto idx, auto *entity) -> void {
                if (child_->isSelected() && idx >= entity->class_info->attributes.count()) {
                    entity->class_info->remove_method(
                            idx - 1 - entity->class_info->attributes.count()
                    );
                    entity->update_elements();
                }
            });
}

QList<Entity *> *Class_diagram::get_selected_entities() {
    QList<Entity *> *rects = new QList<Entity *>;
    for (const QGraphicsItem *item: scene->selectedItems()) {
        if (item->data(0).toString() == "entity") {
            rects->push_back((Entity *) item);
        }
    }
    return rects;
}

void Class_diagram::connect_classes() {
    QList<Entity *> *rects = get_selected_entities();
    if (rects->count() < 2) {
        QMessageBox::critical(nullptr, "Error", "Please select just 2 classes", "OK");
    } else {
        create_connection(rects, "relation_name");
    }
}

void Class_diagram::create_connection(QList<Entity *> *rects, const QString &name) {
    Relation_line::Type t1 = Relation_line::ASSOCIATION;
    QComboBox *p1_combo_box = side_toolbox->p1_combo_box;
    if (p1_combo_box->currentText() == "Aggregation") { t1 = Relation_line::AGGREGATION; }
    if (p1_combo_box->currentText() == "Composition") { t1 = Relation_line::COMPOSITION; }
    if (p1_combo_box->currentText() == "Generalization") { t1 = Relation_line::GENERALIZATION; }

    Relation_line::Type t2 = Relation_line::ASSOCIATION;
    QComboBox *p2_combo_box = side_toolbox->p2_combo_box;
    if (p2_combo_box->currentText() == "Aggregation") { t2 = Relation_line::AGGREGATION; }
    if (p2_combo_box->currentText() == "Composition") { t2 = Relation_line::COMPOSITION; }
    if (p2_combo_box->currentText() == "Generalization") { t2 = Relation_line::GENERALIZATION; }

    auto relation = new Relation_line((*rects)[0], (*rects)[1], t1, t2, name);
    scene->addItem(relation);
}

void Class_diagram::disconnect_classes() {
    for (auto &item: scene->selectedItems()) {
        if (item->data(0).toString() == "relation_line") {
            auto item_ = (Relation_line *) item;
            item_->delete_points();
            delete item;
        }
    }
}

void Class_diagram::update_connection([[maybe_unused]]const QString &text) {
    Relation_line *line = get_relation_line();
    if (line) {
        auto e1 = (Entity *) line->relation_point1->parentItem();
        auto e2 = (Entity *) line->relation_point2->parentItem();
        const QString name = line->name->text;
        disconnect_classes();
        scene->clearSelection();
        if (side_toolbox->p1_combo_box->currentText() == text) {
            e2->setSelected(true);
            e1->setSelected(true);
        } else if (side_toolbox->p2_combo_box->currentText() == text) {
            e1->setSelected(true);
            e2->setSelected(true);
        }
        create_connection(get_selected_entities(), name);
    }
}

Relation_line *Class_diagram::get_relation_line() {
    if (scene->selectedItems().count() > 1) {
        return nullptr;
    }
    for (const auto child: scene->selectedItems()) {
        if (child->data(0).toString() == "relation_line") {
            return (Relation_line *) child;
        }
    }
    return nullptr;
}

Entity *Class_diagram::get_entity_by_name(const QString &name, QGraphicsScene *scene) {
    for (const auto &item: scene->items()) {
        if (Class_diagram::is_entity(item)) {
            const auto entity = (Entity *) item;
            if (entity->class_info->name == name) {
                return entity;
            }
        }
    }
    return nullptr;
}

void Class_diagram::add_text_item() {
    scene->addItem(new Text_item());
}

void Class_diagram::delete_text_item() {
    for (auto *item: scene->selectedItems()) {
        auto text = (Text_item *) item;
        if (text->data(0).toString() == "text_item") {
            delete text;
        }
    }
}

void Class_diagram::change_class_name(QGraphicsScene *s, const QString &old_string,
                                      const QString &new_string) {
    for (auto &entity: s->items()) {
        auto entity_ = ((Entity *) entity);
        if (entity->data(0).toString() == "entity" && entity_->class_info->name == old_string) {
            entity_->class_info->update_name(new_string);
            entity_->update_elements();
        }
    }
}

void Class_diagram::change_class_method(QGraphicsScene *s, const QString &entity_name,
                                        const QString &old_string, const QString &new_string) {

    auto update_method = [=](Entity *entity_) {
        auto methods = entity_->class_info->methods;
        for (int i = 0; i < entity_->class_info->methods.count(); i++) {
            if (methods[i].name.split("(")[0] == old_string) {
                methods[i].name = new_string + "(" + methods[i].params + ")";
            }
        }
        entity_->update_elements();
    };

    for (auto &item: s->items()) {
        if (item->data(0).toString() == "entity" &&
            ((Entity *) item)->class_info->name == entity_name) {
            update_method(((Entity *) item));
        }
    }
}
