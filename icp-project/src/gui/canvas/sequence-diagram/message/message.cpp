/**
 * @author Andrej Bínovský (xbinov00)
 * @file message.cpp
 */

#include "src/gui/canvas/sequence-diagram/message/message.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"

Message::Message(QGraphicsRectItem *parent1, QGraphicsRectItem *parent2, qreal l, bool isDashed,
                 bool isBlackArrow, bool isCreated, const QString &n)
        : QGraphicsLineItem(QLineF(parent1->x() + parent1->boundingRect().width() / 2,
                                   parent1->y() + parent1->boundingRect().height() + l,
                                   parent2->x() + parent2->boundingRect().width() / 2,
                                   parent2->y() + parent2->boundingRect().height() + l)),
          parent_from(parent1),
          parent_to(parent2),
          is_dashed(isDashed),
          is_black(isBlackArrow),
          is_created(isCreated),
          name(new Textfield_message(n, this)),
          p1(new Point(QRectF(parent1->boundingRect().center().x() - 4,
                              l + parent1->boundingRect().height() - 4, 8, 8),
                       true,
                       parent1,
                       parent2)),
          p2(new Point(
                  QRectF(parent2->boundingRect().center().x(), l + parent2->boundingRect().height(),
                         0, 0),
                  false,
                  parent2,
                  parent1)) {
    p1->setBrush(Qt::red);
    p2->setBrush(Qt::black);
    p1->neighbour_point = p2;
    p2->neighbour_point = p1;
    p1->addLine(this);
    p2->addLine(this);

    if (isBlackArrow) {
        p2->arrow->setBrush(Qt::black);
    }
    if (isDashed) {
        QPen pen;
        pen.setDashPattern({0, 1, 8, 3});
        setPen(pen);
    }
    p1->rotate_arrow();
    setData(0, "message");
    name->old_string = n;
    /* static len -> when line is created */
    setData(1, l);
    /* dynamic len -> init len */
    setData(2, l);
}

QJsonObject *Message::get_message_data() {
    auto json = new QJsonObject;
    json->insert("parent_from", QJsonValue::fromVariant(get_name(parent_from)));
    json->insert("parent_to", QJsonValue::fromVariant(get_name(parent_to)));
    json->insert("len", QJsonValue::fromVariant((int) data(2).toDouble()));
    json->insert("name", QJsonValue::fromVariant(name->toPlainText()));
    json->insert("is_dashed", QJsonValue::fromVariant(is_dashed));
    json->insert("is_black", QJsonValue::fromVariant(is_black));
    json->insert("is_created", QJsonValue::fromVariant(is_created));
    return json;
}

QString Message::get_name(QGraphicsItem *entity) {
    if (entity->data(0) == "actor") {
        return ((Actor *) entity)->name->toPlainText();
    }
    if (entity->data(0) == "object") {
        return ((Object_e *) entity)->name->toPlainText();
    }
    return "";
}


/* Textfield Class */
Textfield_message::Textfield_message(const QString &string, QGraphicsItem *p)
        : QGraphicsTextItem(string, p), parent(p) {
    if (((Message *) parent)->is_created) {
        setPlainText("<<create>>");
    } else {
        setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable |
                                Qt::TextInteractionFlag::TextSelectableByKeyboard |
                                Qt::TextInteractionFlag::TextSelectableByMouse);
    }
    set_pos();
}

void Textfield_message::keyReleaseEvent(QKeyEvent *event) {
    Class_diagram::change_class_method(scene(),
                                       Message::get_name(((Message *) parent)->parent_to),
                                       old_string,
                                       toPlainText());
    old_string = toPlainText();
    set_pos();
    (void) event;
}

void Textfield_message::set_pos() {
    setPos(
            parent->boundingRect().center().x() - QGraphicsTextItem::boundingRect().width() / 2,
            parent->boundingRect().center().y() - QGraphicsTextItem::boundingRect().height() / 2 -
            10
    );
}
