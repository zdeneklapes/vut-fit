/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file entity.cpp
 */

#include "src/gui/canvas/class-diagram/entity/entity.h"

Entity::Entity(QGraphicsScene *scene, Class_info *info)
        : QGraphicsRectItem(0, 0, 10, 10), class_info(info),
          parent(scene) {
    setData(0, "entity");
    setFlags(QGraphicsRectItem::ItemIsSelectable |
             QGraphicsRectItem::ItemIsMovable |
             QGraphicsRectItem::ItemSendsScenePositionChanges);
    create_elements();
}

void Entity::create_elements() {
//  NAME
    auto text_item = new Entity_text(class_info->name, this);
    text_item->setPos(0, 0);
    setRect(refactor_rect());

//  ATTRIBS + METHODS
    for (const auto &elem: class_info->attributes + class_info->methods) {
        text_item = new Entity_text(
                QString("%0 : %1 : %2").arg(elem.visibility).arg(elem.name).arg(elem.type), this
        );
        text_item->setPos(0, new_y_text_item());
    }
    setRect(refactor_rect());
    setPos(x(), y()); // need's to be done after everything is generated
    create_separator(text_item);
}

void Entity::remove_elements() {
    for (auto child: childItems()) {
        if (child->data(0).toString() == "entity_text" ||
            child->data(0).toString() == "entity_divider") {
            delete child;
        }
    }
    setRect(refactor_rect());
}

void Entity::update_elements() {
    remove_elements();
    create_elements();
}

void Entity::create_separator(Entity_text *text) {
    int text_height = text->boundingRect().height();
    line1 = new QGraphicsLineItem(0, text_height, this->boundingRect().width(), text_height, this);
    line2 = new QGraphicsLineItem(0, (text_height * (class_info->attributes.count() + 1)),
                                  this->boundingRect().width(),
                                  (text_height * (class_info->attributes.count() + 1)), this);
    line1->setData(0, "entity_divider");
    line2->setData(0, "entity_divider");
}

void Entity::update_separator() {
    line1->setLine(line1->line().p1().x(), line1->line().p1().y(),
                   line1->line().p1().x() + refactor_rect().width() - 1, line1->line().p2().y());
    line2->setLine(line2->line().p1().x(), line2->line().p1().y(),
                   line2->line().p1().x() + refactor_rect().width() - 1, line2->line().p2().y());
}

QList<Entity_text *> *Entity::get_text_item_child(Entity *entity) {
    QList<Entity_text *> *list = new QList<Entity_text *>;
    for (const auto child: entity->childItems()) {
        if (child->data(0).toString() == "entity_text") {
            list->push_back((Entity_text *) child);
        }
    }
    return list;
}

int Entity::new_y_text_item() {
    int children_count = childItems().count() - 2;  // -2 because "this" child already exist and -1
    if (children_count == -1) { return 0; }
    auto last_item = childItems()[children_count];
    return (int) (last_item->y() + last_item->boundingRect().height());
}

QRect Entity::refactor_rect(Entity *entity) { // default nullptr
    Entity *entity_ = entity ? entity : this;
    int width = 0, height = 0;
    for (const auto &child: entity_->childItems()) {
        if (child->data(0).toString() == "entity_text") {  // TextItem
            auto child_ = (Entity_text *) child;
            width = (width < child_->boundingRect().width())
                    ? (int) child_->boundingRect().width()
                    : width;
            height += child_->boundingRect().height();
        }
    }
    return {0, 0, width, height}; // generating in pos(0,0)
}

QVariant Entity::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange) {
        Window::stack->push(new Cmd_move_entity(this->scene(), this));
    }
    return QGraphicsItem::itemChange(change, value);
}

Entity::~Entity() = default;


QJsonObject *Entity::get_entity_info() {
    auto json = new QJsonObject;
    auto coordinates_ = new QJsonObject;
    auto class_info_ = new QJsonObject;
    auto attributes = new QJsonArray;
    auto methods = new QJsonArray;
    coordinates_->insert("x", QJsonValue::fromVariant((int) x()));
    coordinates_->insert("y", QJsonValue::fromVariant((int) y()));
    class_info_->insert("name", QJsonValue::fromVariant(class_info->name));
    // attributes
    for (const auto &elem: class_info->attributes) {
        auto *obj = new QJsonObject;
        obj->insert("visibility", QJsonValue::fromVariant(elem.visibility));
        obj->insert("name", QJsonValue::fromVariant(elem.name));
        obj->insert("type", QJsonValue::fromVariant(elem.type));
        attributes->push_back(QJsonValue::fromVariant(*obj));
    }
    // methods
    for (const auto &elem: class_info->methods) {
        auto *obj = new QJsonObject;
        obj->insert("visibility", QJsonValue::fromVariant(elem.visibility));
        obj->insert("name", QJsonValue::fromVariant(elem.name));
        obj->insert("type", QJsonValue::fromVariant(elem.type));
        methods->push_back(QJsonValue::fromVariant(*obj));
    }

    class_info_->insert("attributes", QJsonValue::fromVariant(*attributes));
    class_info_->insert("methods", QJsonValue::fromVariant(*methods));

    json->insert("coordinates", QJsonValue::fromVariant(*coordinates_));
    json->insert("class_info", QJsonValue::fromVariant(*class_info_));
    return json;
}
