/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file verification.cpp
 */

#include "src/core/verification/verification.h"

Verification::Verification(QGraphicsScene *s) : scene(s), error(false) {}

void Verification::verify_sequence_diagram(const QJsonArray &array) {
    Q_FOREACH(auto diagram, array) {
            if (error) {
                return;
            }
            parse_sequence_diagram(diagram.toObject());
        }
}

void Verification::verify_class_diagram(const QJsonObject &object) {
    QMap<QString, int> class_names;
    Q_FOREACH(auto item_value, object["entities"].toArray()) {
            auto item = item_value.toObject();
            auto info = item["class_info"].toObject();
            if (class_names.contains(info["name"].toString())) {
                QMessageBox::critical(nullptr, "Error", "2 or more classes are named same");
                error = true;
                return;
            }
            class_names.insert(info["name"].toString(), 1);
        }
}

void Verification::parse_sequence_diagram(const QJsonObject &json) {
    verify_sequence_diagram_items(json["items"].toArray());
    if (error) {
        return;
    }
    verify_sequence_diagram_messages(json["messages"].toArray(), json["name"].toString());
}

void Verification::verify_sequence_diagram_items(const QJsonArray &items) {
    const auto class_entities = Class_info::get_entities(scene);
    QList<QString> entities;
    if (class_entities == nullptr) {
        return;
    }
    Q_FOREACH(auto item_value, items) {
            auto item = item_value.toObject();
            auto name = item["name"].toString();
            if (entities.contains(name)) {
                QString s = "At least two entities have the same name -> \"";
                s += name;
                s += "\"";
                QMessageBox::critical(nullptr, "", s);
                error = true;
                return;
            }
            entities.append(name);
            if (!class_entities->contains(name)) {
                QString s = "Name of actor or object \"";
                s += name;
                s += "\" is not exist in class diagram";
                QMessageBox::critical(nullptr, "", s);
                error = true;
                return;
            }
        }
}

void Verification::verify_sequence_diagram_messages(const QJsonArray &messages,
                                                    const QString &name_of_diagram) {
    const auto class_entities = Class_info::get_entities(scene);
    if (class_entities == nullptr) {
        return;
    }
    Q_FOREACH(auto item, messages) {
            auto mess = item.toObject();
            QGraphicsRectItem *parent_to = nullptr;
            Q_FOREACH(auto entity, scene->items()) {
                    if (name_of_diagram == entity->data(10) and
                        Message::get_name(entity) == mess["parent_to"].toString()) {
                        parent_to = (QGraphicsRectItem *) entity;
                    }
                }
            if (parent_to != nullptr and !mess["is_dashed"].toBool() and !mess["is_created"].toBool() and
                !(*class_entities)[Message::get_name(parent_to)].contains(
                        mess["name"].toString())) {
                QString s = "Method \"";
                s += mess["name"].toString();
                s += "\" is not exist in class \"";
                s += Message::get_name(parent_to);
                s += "\"";
                QMessageBox::critical(nullptr, "", s);
                error = true;
                return;
            }
        }
}
