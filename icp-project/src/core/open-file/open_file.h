/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file open_file.h
 */

#ifndef DIAGRAM_EDITOR_OPEN_FILE_H
#define DIAGRAM_EDITOR_OPEN_FILE_H

#include <QJsonObject>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"
#include "src/gui/canvas/sequence-diagram/actor/actor.h"
#include "src/gui/canvas/sequence-diagram/object/object.h"
#include "src/gui/canvas/sequence-diagram/box/box.h"
#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"
#include "src/gui/canvas/class-diagram/entity/entity.h"
#include "src/gui/canvas/class-diagram/entity/class_info/class_info.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"
#include "src/gui/canvas/class-diagram/relation/relation_line.h"

class Open_file : public QObject {
public:
    Open_file(QGraphicsScene *scene);

private:
    QGraphicsScene *scene;

    void parse_class_diagram(const QJsonObject &json);

    void parse_array_sequence_diagrams(const QJsonArray &array);

    void parse_sequence_diagram(const QJsonObject &json);

    void create_sequence_diagram_items(const QJsonArray &items, const QString &name_of_diagram);

    void create_sequence_diagram_messages(const QJsonArray &messages, const QString &name_of_diagram);

    void parse_class_diagram_entities(const QJsonObject &json);

    void parse_class_diagram_relations(const QJsonObject &json);

public slots:

    void open_file();

    void parse_class_diagram_texts(const QJsonObject &json);
};


#endif //DIAGRAM_EDITOR_OPEN_FILE_H
