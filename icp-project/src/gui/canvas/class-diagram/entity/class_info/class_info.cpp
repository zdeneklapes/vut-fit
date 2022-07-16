/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file class_info.cpp
 */

#include "src/gui/canvas/class-diagram/entity/class_info/class_info.h"
#include "src/gui/canvas/class-diagram/entity/entity.h" // forwarding

Element::Element(QString vis, QString attrib_name, QString attrib_type) :
        visibility(std::move(vis)),
        name(std::move(attrib_name)),
        type(std::move(attrib_type)) {
    update_params();
}

Element::~Element() = default;

/************************************************************************************* NEXT_CLASS */

void Element::update_params() {
    params =
            name.indexOf("(") < name.indexOf(")") &&
            name.indexOf("(") >= 0 &&
            name.indexOf(")") >= 0
            ? name.split("(")[1].split(")")[0]
            : "";
}

Class_info::Class_info() :
        name(QString("Class1")),
        attributes(QList<Element>()),
        methods(QList<Element>()) {
    insert_new_attribute(attributes.count());
    insert_new_method(methods.count());
}


bool Class_info::update_name(const QString &str) {
    if (str.isEmpty()) {
        QMessageBox::critical(nullptr, "Error", "Class name can't be empty");
        return false;
    } else {
        set_name(str);
        return true;
    }
}

void Class_info::set_name(const QString &str) {
    name.clear();
    name.append(str);
}

void Class_info::insert_new_attribute(const int at) {
    attributes.insert(at, Element("+", QString("attribute_%0").arg(attributes.count()),
                                  "type"));
}

void Class_info::insert_attribute(const Element element) {
    attributes.append(element);
}

bool Class_info::update_attribute(const int at, const QString &str) {
    auto line_part = verify_new_element(str);
    if (line_part) {
        attributes[at].visibility = (*line_part)[0];
        attributes[at].name = (*line_part)[1];
        attributes[at].type = (*line_part)[2];
        return true;
    }
    return false;
}

void Class_info::remove_attribute(const int at) {
    attributes.removeAt(at);
}

void Class_info::insert_new_method(const int at) {
    methods.insert(at, Element("+", QString("method_%0()").arg(methods.count()), "type"));
}

void Class_info::insert_method(const Element &element) {
    methods.append(element);
}


bool Class_info::update_method(const int at, const QString &str) {
    auto line_part = verify_new_element(str);
    if (line_part) {
        methods[at].visibility = (*line_part)[0];
        methods[at].name = (*line_part)[1];
        methods[at].type = (*line_part)[2];
        methods[at].update_params();
        return true;
    }
    return false;
}

void Class_info::remove_method(const int at) {
    methods.removeAt(at);
}

QStringList *Class_info::verify_new_element(const QString &str) {
    auto line = str;
    QString args = "";
    if (str.indexOf("(") < str.indexOf(")") && str.indexOf("(") >= 0 && str.indexOf(")") >= 0) {
        args = "("+str.split("(")[1].split(")")[0] +")";
        line = str.split("(")[0] + str.split(")")[1];
    }
    auto line_parts = new QStringList(line.split(":"));
    for (auto &part: *line_parts) { part = part.trimmed(); }
    if ((line_parts->count() != 3) ||
        ((*line_parts)[0] != "+" &&
         (*line_parts)[0] != "-" &&
         (*line_parts)[0] != "#" &&
         (*line_parts)[0] != "~") ||
        (*line_parts)[0].count() == 0 ||
        (*line_parts)[1].count() == 0 ||
        (*line_parts)[2].count() == 0 ||
        str.contains("\n")) {
        QMessageBox::critical(0, "Error", "Your input is incorrect:\n\n"
                                          "Signature:\t [visibility] : [name] : [type]\n\n"
                                          "Examples:\t '+ : attribute_name : int\n"
                                          "Examples:\t '- : method_name() : int\n\n"
                                          "Visibility allowed characters: '+' ; '-' ; '#' ; '~'\n\n"
                                          "Forbidden character are: '\\n'",
                              "OK");
        return nullptr;
    }
    (*line_parts)[1] = (*line_parts)[1] + args;
    return line_parts;
}

QMap<QString, QList<QString>> *Class_info::get_entities(QGraphicsScene *scene) {
    auto info = new QMap<QString, QList<QString>>();
    for (const auto &item: scene->items()) {
        if (item->data(0).toString() == "entity") {
            const auto &item_ = (Entity *) item;
            QList<QString> methods;
            for (const auto &method: item_->class_info->methods) {
                methods.push_back(method.name.split("(")[0]);
            }
            info->insert(item_->class_info->name, methods);
        }
    }
    return info;
}

Class_info::~Class_info() = default;
