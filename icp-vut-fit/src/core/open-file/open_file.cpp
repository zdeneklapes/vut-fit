/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file open_file.cpp
 */

#include "src/core/open-file/open_file.h"

Open_file::Open_file(QGraphicsScene *scene) :
        scene(scene) {}

void Open_file::open_file() {
    auto fileName = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Open File"), "./",
                                                 tr("Json (*.json)"));
    if (!fileName.isEmpty()) {
        auto file = new QFile(fileName);
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox msgBox;
            msgBox.setText("Couldn't open file");
            msgBox.exec();
            return;
        }
        auto json_doc = QJsonDocument::fromJson(file->readAll());
        QJsonObject json = json_doc.object();
        scene->clear();
        parse_class_diagram(json.value("class_diagram").toObject());
        parse_array_sequence_diagrams(json.value("sequence_diagram").toArray());

        file->close();
    }
}

void Open_file::parse_class_diagram_entities(const QJsonObject &json) {
    Q_FOREACH(auto item_value, json["entities"].toArray()) {
            auto item = item_value.toObject();
            auto coords = item["coordinates"].toObject();
            auto info = item["class_info"].toObject();
            auto *class_info = new Class_info();

            class_info->set_name(info["name"].toString());

            class_info->attributes.clear();
            Q_FOREACH(auto elem, info["attributes"].toArray()) {
                    class_info->insert_attribute(Element(elem.toObject()["visibility"].toString(),
                                                         elem.toObject()["name"].toString(),
                                                         elem.toObject()["type"].toString()));
                }

            class_info->methods.clear();
            Q_FOREACH(auto elem, info["methods"].toArray()) {
                    class_info->insert_method(
                            Element(elem.toObject()["visibility"].toString(),
                                    elem.toObject()["name"].toString(),
                                    elem.toObject()["type"].toString()));
                }
            auto entity = new Entity(scene, class_info);
            entity->setPos(coords["x"].toInt(), coords["y"].toInt());
            scene->addItem(entity);
        }
}

void Open_file::parse_class_diagram_relations(const QJsonObject &json) {
    Q_FOREACH(auto item_value, json["relations"].toArray()) {
            auto entity_name1 = item_value.toObject()["entity1"].toString();
            auto entity_name2 = item_value.toObject()["entity2"].toString();

            auto name = item_value.toObject()["name"].toString();

            auto relation_type1 = item_value.toObject()["type1"].toString();
            auto relation_type2 = item_value.toObject()["type2"].toString();

            Entity *entity1 = Class_diagram::get_entity_by_name(entity_name1, scene);
            Entity *entity2 = Class_diagram::get_entity_by_name(entity_name2, scene);

            auto relation = new Relation_line(entity1,
                                              entity2,
                                              Relation_line::get_relation_type(relation_type1),
                                              Relation_line::get_relation_type(relation_type2),
                                              name);
            scene->addItem(relation);
        }
}

void Open_file::parse_class_diagram_texts(const QJsonObject &json) {
    Q_FOREACH(auto item_value, json["texts"].toArray()) {
            auto x = item_value.toObject()["x"].toInt();
            auto y = item_value.toObject()["y"].toInt();
            auto text = item_value.toObject()["text"].toString();

            auto *text_item = new Text_item(text);
            text_item->setPos(x, y);
            scene->addItem(text_item);
        }
}

void Open_file::parse_class_diagram(const QJsonObject &json) {
    parse_class_diagram_entities(json);
    parse_class_diagram_relations(json);
    parse_class_diagram_texts(json);
}


void Open_file::parse_array_sequence_diagrams(const QJsonArray &array) {
    Q_FOREACH(auto diagram, array) {
            parse_sequence_diagram(diagram.toObject());
        }
}

void Open_file::parse_sequence_diagram(const QJsonObject &json) {
    auto diagram_name = json["name"].toString();
    Input_entity::diagram_name = diagram_name;
    Lifeline::size[diagram_name] = (qreal) json["lifeline"].toInt();
    create_sequence_diagram_items(json["items"].toArray(), diagram_name);
    create_sequence_diagram_messages(json["messages"].toArray(), diagram_name);
}

void Open_file::create_sequence_diagram_items(const QJsonArray &items, const QString &name_of_diagram) {
    Q_FOREACH(auto item_value, items) {
            auto item = item_value.toObject();
            if (item["type"] == "actor") {
                auto pos = item["coordinates"].toObject();
                auto actor = new Actor(pos["x"].toInt(), pos["y"].toInt(), pos["s"].toInt(),
                                       item["name"].toString());
                actor->setData(10, name_of_diagram);
                scene->addItem(actor);
                Q_FOREACH(auto box, item["boxes"].toArray()) {
                        auto b = box.toObject();
                        auto box_a = new Box(b["y"].toInt(), b["s"].toInt(), actor->lifeline);
                        box_a->setData(10, name_of_diagram);
                    }

            } else if (item["type"] == "object") {
                auto pos = item["coordinates"].toObject();
                auto object = new Object_e(pos["x"].toInt(), pos["y"].toInt(), pos["s"].toInt(),
                                           item["name"].toString());
                object->setData(10, name_of_diagram);
                scene->addItem(object);
                Q_FOREACH(auto box, item["boxes"].toArray()) {
                        auto b = box.toObject();
                        auto box_o = new Box(b["y"].toInt(), b["s"].toInt(), object->lifeline);
                        box_o->setData(10, name_of_diagram);
                    }
            }
        }
}

void Open_file::create_sequence_diagram_messages(const QJsonArray &messages, const QString &name_of_diagram) {
    Q_FOREACH(auto item, messages) {
            auto mess = item.toObject();
            QGraphicsRectItem *parent_from = nullptr;
            QGraphicsRectItem *parent_to = nullptr;
            Q_FOREACH(auto entity, scene->items()) {
                    if (name_of_diagram == entity->data(10)) {
                        if (Message::get_name(entity) == mess["parent_from"].toString())
                            parent_from = (QGraphicsRectItem *) entity;
                        if (Message::get_name(entity) == mess["parent_to"].toString())
                            parent_to = (QGraphicsRectItem *) entity;
                    }
                }
            if (parent_to != nullptr and parent_from != nullptr) {
                auto message = new Message(parent_from, parent_to, mess["len"].toInt(),
                                           mess["is_dashed"].toBool(),
                                           mess["is_black"].toBool(), mess["is_created"].toBool(),
                                           mess["name"].toString());
                message->setData(10, name_of_diagram);
                scene->addItem(message);
            }
        }
}
