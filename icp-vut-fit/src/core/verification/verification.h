/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file verification.h
 */


#ifndef DIAGRAM_EDITOR_VERIFICATION_H
#define DIAGRAM_EDITOR_VERIFICATION_H


#include <QJsonObject>
#include <QGraphicsScene>
#include <QJsonArray>
#include <QMessageBox>
#include <QMap>
#include "src/gui/canvas/class-diagram/entity/class_info/class_info.h"
#include "src/gui/canvas/sequence-diagram/message/message.h"


class Verification {
public:
    Verification(QGraphicsScene *s);

    void verify_sequence_diagram(const QJsonArray &array);

    void parse_sequence_diagram(const QJsonObject &json);

    void verify_sequence_diagram_items(const QJsonArray &items);

    void verify_sequence_diagram_messages(const QJsonArray &messages, const QString &name_of_diagram);

    QGraphicsScene *scene;
    bool error;

    void verify_class_diagram(const QJsonObject &object);
};


#endif //DIAGRAM_EDITOR_VERIFICATION_H
