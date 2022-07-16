/**
 * @author Andrej Bínovský (xbinov00)
 * @file object.h
 */

#ifndef DIAGRAM_EDITOR_OBJECT_H
#define DIAGRAM_EDITOR_OBJECT_H

#include <QGraphicsItem>
#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"

class Class_diagram;

/**
 * @class Textfield_object
 * @brief Handle text name of object
 */
class Textfield_object : public QGraphicsTextItem {
public:
    /**
     * @param string Initial string
     * @param p Object parent
     */
    Textfield_object(const QString &string, QGraphicsItem *p);

    /**
     * @brief Centre position of text
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * @brief Set position of text after change
     */
    void set_pos();

    QString old_string;

private:
    /**
     * @brief Object parent
     */
    QGraphicsItem *parent;
};

/**
 * @class Object_e
 * @brief Represents object as item
 */
class Object_e : public QGraphicsRectItem {
public:
    /**
     * @param x Position of object (x)
     * @param y Position of object (y)
     * @param s Size of object. Width and height
     * @param n Name of Object
     */
    Object_e(qreal x, qreal y, qreal s, const QString &n);

    /**
     * @brief Handle collect data of Object into json
     * @return Json object with data
     */
    QJsonObject *get_object_data();

    Textfield_object *name;
    Lifeline *lifeline;
};

#endif //DIAGRAM_EDITOR_OBJECT_H
