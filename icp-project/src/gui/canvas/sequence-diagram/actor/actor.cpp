/**
 * @author Andrej Bínovský (xbinov00)
 * @file actor.cpp
 */

#include "src/gui/canvas/sequence-diagram/actor/actor.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"

Actor::Actor(qreal x, qreal y, qreal s, const QString &n) :
        QGraphicsRectItem(0, 0, s, s * 4),
        size(s),
        name(new Textfield_actor(n, this)),
        lifeline(new Lifeline(size / 2, size * 4, this)),
        head(new QGraphicsEllipseItem(this)),
        body(new QGraphicsLineItem(this)),
        hands(new QGraphicsLineItem(this)),
        left_leg(new QGraphicsLineItem(this)),
        right_leg(new QGraphicsLineItem(this)) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsScenePositionChanges);
    set_body();
    setPos(x, y);
    setData(0, "actor");
    setData(1, n);
    QPen pen;
    pen.setColor(Qt::white);
    setPen(pen);
    name->old_string = n;
}


void Actor::set_body() {
    auto body_start_y = size;
    auto body_end_y = size * 2.5;
    auto body_x = size / 2;
    auto hands_start_x = 0;
    auto hands_end_x = size;
    auto hand_y = size + size / 3;
    auto legs_start_x = size / 2;

    auto leg_left_end_x = 0;
    auto leg_right_end_x = size;
    auto legs_start_y = size * 2.5;
    auto legs_end_y = size * 4;

    /* head */
    head->setRect(0, 0, size, size);
    /* body */
    body->setLine(body_x, body_start_y, body_x, body_end_y);
    /* hands */
    hands->setLine(hands_start_x, hand_y, hands_end_x, hand_y);
    /* left leg */
    left_leg->setLine(legs_start_x, legs_start_y, leg_left_end_x, legs_end_y);
    /* right leg */
    right_leg->setLine(legs_start_x, legs_start_y, leg_right_end_x, legs_end_y);
}

QJsonObject *Actor::get_actor_data() {
    auto json = new QJsonObject;
    auto coordinates = new QJsonObject;
    coordinates->insert("x", QJsonValue::fromVariant((int) x()));
    coordinates->insert("y", QJsonValue::fromVariant((int) y()));
    coordinates->insert("s", QJsonValue::fromVariant((int) size));
    json->insert("type", QJsonValue::fromVariant("actor"));
    json->insert("name", QJsonValue::fromVariant(name->toPlainText()));
    json->insert("coordinates", QJsonValue::fromVariant(*coordinates));
    json->insert("boxes", QJsonValue::fromVariant(*(lifeline->get_boxes())));
    return json;
}


/* Textfield Class */
Textfield_actor::Textfield_actor(const QString &string, QGraphicsItem *p)
        : QGraphicsTextItem(string, p), parent(p) {

    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable |
                            Qt::TextInteractionFlag::TextSelectableByKeyboard |
                            Qt::TextInteractionFlag::TextSelectableByMouse);
    set_pos();
}

void Textfield_actor::keyReleaseEvent(QKeyEvent *event) {
    Class_diagram::change_class_name(scene(), old_string, toPlainText());
    old_string = toPlainText();
    set_pos();
    (void) event;
}

void Textfield_actor::set_pos() {
    setPos(parent->boundingRect().center().x() - QGraphicsTextItem::boundingRect().width() / 2,
           ((Actor *) parent)->size * 4);
}

