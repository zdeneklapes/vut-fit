/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file entity_text.cpp
 */

#include "src/gui/canvas/class-diagram/entity/entity-text/entity_text.h"
#include "src/gui/canvas/class-diagram/entity/entity.h" // forward
#include "src/gui/canvas/class-diagram/undo-redo/undo_redo.h" // forward
#include "src/gui/window.h"

Entity_text::Entity_text(const QString &str, Entity *p) : QGraphicsTextItem(str, p), parent(p) {
    setFlags(QGraphicsTextItem::ItemIsSelectable);
    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable |
                            Qt::TextInteractionFlag::TextSelectableByKeyboard |
                            Qt::TextInteractionFlag::TextSelectableByMouse);
    setPos(0, y());
    setData(0, "entity_text");
}

Entity_text::~Entity_text() = default;

void Entity_text::keyReleaseEvent(QKeyEvent * /*event*/) {
    setPos(0, y());
    parent->setRect(parent->refactor_rect(parent));
    parent->update_separator();
}

void Entity_text::focusOutEvent(QFocusEvent *event) {
    auto list = parent->get_text_item_child(parent); // because child conatins all

    auto changing_name = [=]() {
        auto last_string = QString("%0").arg(parent->class_info->name);
        if (!parent->class_info->update_name(toPlainText())) {
            setPlainText(QString("%0").arg(parent->class_info->name));
        } else {
            Window::stack->push(new Cmd_text_changed_entity(this, last_string));
            Sequence_diagram::change_entity_name(this->scene(), last_string,
                                                 parent->class_info->name);
        }
    };

    auto changing_attribute = [=](int idx) {
        auto last_string = QString("%0 : %1 : %2")
                .arg(parent->class_info->attributes[idx].visibility)
                .arg(parent->class_info->attributes[idx].name)
                .arg(parent->class_info->attributes[idx].type);

        if (!parent->class_info->update_attribute(idx, toPlainText())) {
            setPlainText(last_string);
        } else {
            Window::stack->push(new Cmd_text_changed_entity(this, last_string));
        }
    };

    auto changing_method = [=](int idx) {
        int new_idx = idx - parent->class_info->attributes.count();

        auto last_string = QString("%0 : %1 : %2")
                .arg(parent->class_info->methods[new_idx].visibility)
                .arg(parent->class_info->methods[new_idx].name)
                .arg(parent->class_info->methods[new_idx].type);
        auto last_method_name = QString("%0").arg(
                parent->class_info->methods[new_idx].name.split("(")[0]);

        if (!parent->class_info->update_method(new_idx, toPlainText())) {
            setPlainText(last_string);
        } else {
            Window::stack->push(new Cmd_text_changed_entity(this, last_string));
            Sequence_diagram::change_message_name(this->scene(),
                                                  last_method_name,
                                                  parent->class_info->methods[new_idx].name.split(
                                                          "(")[0],
                                                  parent->class_info->name);
        }
    };

    for (int i = 0; i < list->count(); ++i) {
        Entity_text *child_ = (*list)[i];
        if (this == child_) {
            int idx = i - 1;
            if (i == 0) {
                changing_name();
            } else if (idx < parent->class_info->attributes.count()) {  // attribute
                changing_attribute(idx);
            } else {  // method
                changing_method(idx);
            }
        }
    }
    // must be here to clearFocus && remove cursor otherwise doing interesting things :D
    return QGraphicsTextItem::focusOutEvent(event);
}
