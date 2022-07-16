/**
 * @author Andrej Bínovský (xbinov00)
 * @file object.cpp
 */

#include "src/gui/canvas/sequence-diagram/object/object.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"

Object_e::Object_e(qreal x, qreal y, qreal s, const QString &n)
        : QGraphicsRectItem(0, 0, s * 2, s),
          name(new Textfield_object(n, this)),
          lifeline(new Lifeline(s, s, this)) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsScenePositionChanges);
    name->old_string = n;
    setPos(x, y);
    setData(0, "object");
}

QJsonObject *Object_e::get_object_data() {
    auto json = new QJsonObject;
    auto coordinates = new QJsonObject;
    coordinates->insert("x", QJsonValue::fromVariant((int) this->pos().x()));
    coordinates->insert("y", QJsonValue::fromVariant((int) this->pos().y()));
    coordinates->insert("s", QJsonValue::fromVariant((int) this->boundingRect().height()));
    json->insert("type", QJsonValue::fromVariant("object"));
    json->insert("name", QJsonValue::fromVariant(name->toPlainText()));
    json->insert("boxes", QJsonValue::fromVariant(*(lifeline->get_boxes())));
    json->insert("coordinates", QJsonValue::fromVariant(*coordinates));
    return json;
}

/* Textfield Class */
Textfield_object::Textfield_object(const QString &string, QGraphicsItem *p)
        : QGraphicsTextItem(string, p), parent(p) {
    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable |
                            Qt::TextInteractionFlag::TextSelectableByKeyboard |
                            Qt::TextInteractionFlag::TextSelectableByMouse);
    set_pos();
}

void Textfield_object::keyReleaseEvent(QKeyEvent *event) {
    Class_diagram::change_class_name(scene(), old_string, toPlainText());
    old_string = toPlainText();
    set_pos();
    (void) event;
}

void Textfield_object::set_pos() {
    this->setPos(
            parent->boundingRect().center().x() - QGraphicsTextItem::boundingRect().width() / 2,
            QGraphicsTextItem::boundingRect().height() * 2);
}
