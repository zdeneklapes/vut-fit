/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file save_file.cpp
 */

#include "src/core/save-file/save_file.h"

Save_file::Save_file(QGraphicsScene *scene) :
        scene(scene) {}

void Save_file::save_file() {
    auto verification = new Verification(scene);
    auto json = new QJsonObject();
    auto sequence_diagram_json = *(create_sequence_diagram_json());
    auto class_diagram_json = *(create_class_diagram_json());
    verification->verify_class_diagram(class_diagram_json);
    verification->verify_sequence_diagram(sequence_diagram_json);
    if (verification->error) {
        return;
    }

    json->insert("sequence_diagram", sequence_diagram_json);
    json->insert("class_diagram", class_diagram_json);

    auto fileName = QFileDialog::getSaveFileName(Q_NULLPTR, tr("Save File"), "./",
                                                 tr("Json (*.json)"));
    if (!fileName.isEmpty()) {
        auto file = new QFile(fileName);
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox msgBox;
            msgBox.setText("Couldn't save file");
            msgBox.exec();
            return;
        }
        QJsonDocument doc(*json);
        QTextStream out(file);
        out << doc.toJson();
        file->close();
    }
}

QJsonObject *Save_file::create_class_diagram_json() {
    auto json = new QJsonObject();
    auto all_items = scene->items();

    auto entities = new QJsonArray();
    auto relations = new QJsonArray();
    auto texts = new QJsonArray();

    Q_FOREACH(auto item, all_items) {
            if (item->isVisible()) {
                if (item->data(0).toString() == "entity") {
                    entities->push_back(*((Entity *) item)->get_entity_info());
                } else if (item->data(0).toString() == "relation_line") {
                    relations->push_back(*((Relation_line *) item)->get_relation_line_info());
                } else if (item->data(0).toString() == "text_item") {
                    texts->push_back(*((Text_item *) item)->get_text_item_info());
                }
            }
        }
    json->insert("entities", *entities);
    json->insert("relations", *relations);
    json->insert("texts", *texts);
    return json;
}

QJsonArray *Save_file::create_sequence_diagram_json() {
    auto json = new QJsonArray();
    Q_FOREACH(auto name, get_diagram_names()) {
            json->push_back(*get_diagram(name));
        }
    return json;
}


QJsonObject *Save_file::get_diagram(const QString &name) {
    auto items_array = new QJsonArray();
    auto message_array = new QJsonArray();
    auto diagram = new QJsonObject();
    Q_FOREACH(auto item, scene->items()) {
            if (item->data(10) == name) {
                if (item->data(0) == "actor") {
                    items_array->push_back(*((Actor *) item)->get_actor_data());
                }
                if (item->data(0) == "object") {
                    items_array->push_back(*((Object_e *) item)->get_object_data());
                }
                if (item->data(0) == "message") {
                    message_array->push_back(*((Message *) item)->get_message_data());
                }
            }
        }
    diagram->insert("lifeline", Lifeline::size[name]);
    diagram->insert("items", *items_array);
    diagram->insert("messages", *message_array);
    diagram->insert("name", name);
    return diagram;
}

QList<QString> Save_file::get_diagram_names() {
    QList<QString> names;
    Q_FOREACH(auto item, scene->items()) {
            auto name = item->data(10);
            if (name.isValid()) {
                if (!names.contains(name.toString())) {
                    names.append(name.toString());
                }
            }
        }
    return names;
}
