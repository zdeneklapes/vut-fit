/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file save_file.h
 */

#ifndef DIAGRAM_EDITOR_SAVE_FILE_H
#define DIAGRAM_EDITOR_SAVE_FILE_H

#include <QJsonObject>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <QJsonObject>
#include <QJsonValue>
#include <QMap>

#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"
#include "src/gui/canvas/sequence-diagram/actor/actor.h"
#include "src/gui/canvas/sequence-diagram/object/object.h"
#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"
#include "src/gui/canvas/class-diagram/entity/entity.h"
#include "src/gui/canvas/class-diagram/relation/relation_line.h"
#include "src/gui/canvas/class-diagram/entity/class_info/class_info.h"
#include "src/core/verification/verification.h"
#include "src/gui/canvas/class-diagram/text-item/text_item.h"

class Save_file : public QObject, QJsonValue, QJsonObject {
public:
    Save_file(QGraphicsScene *scene);

    QList<QString> get_diagram_names();

private:
    QGraphicsScene *scene;

    QJsonObject *create_class_diagram_json();

    QJsonArray *create_sequence_diagram_json();

    QJsonObject *get_diagram(const QString &name);

public slots:

    void save_file();
};

#endif //DIAGRAM_EDITOR_SAVE_FILE_H
