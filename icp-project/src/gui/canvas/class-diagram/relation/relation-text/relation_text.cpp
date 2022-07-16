/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file relation_text.cpp
 */

#include "src/gui/canvas/class-diagram/relation/relation-text/relation_text.h"
#include "src/gui/canvas/class-diagram/relation/relation_line.h" // forwarding

Relation_text::Relation_text(const QString &str, Relation_line *p)
        : QGraphicsTextItem(str, p), parent(p) {
    setFlags(QGraphicsTextItem::ItemIsSelectable);
    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable |
                            Qt::TextInteractionFlag::TextSelectableByKeyboard |
                            Qt::TextInteractionFlag::TextSelectableByMouse);
    setPos(0, y());
    setData(0, "relation_text");
    text = toPlainText();
}

Relation_text::~Relation_text() = default;

void Relation_text::keyReleaseEvent(QKeyEvent *event) {
    text = toPlainText();
    set_pos();
    return QGraphicsTextItem::keyReleaseEvent(event);
}

void Relation_text::focusOutEvent(QFocusEvent *event) {
    return QGraphicsTextItem::focusOutEvent(event);
}

void Relation_text::set_pos() {
    auto center_width = [=]() { return this->boundingRect().width() / 2; };
    auto center_height = [=]() { return this->boundingRect().height() / 2; };
    setPos(parent->boundingRect().center().x() - center_width(),
           parent->boundingRect().center().y() - center_height());
}

