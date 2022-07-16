/**
 * @author Andrej Bínovský (xbinov00)
 * @file message.h
 */

#ifndef DIAGRAM_EDITOR_MESSAGE_H
#define DIAGRAM_EDITOR_MESSAGE_H

#include <QPen>
#include <QJsonObject>
#include <QJsonArray>

#include "src/gui/canvas/sequence-diagram/message/point/point.h"
#include "src/gui/canvas/sequence-diagram/actor/actor.h"
#include "src/gui/canvas/sequence-diagram/object/object.h"

class Class_diagram;

/**
 * @class Textfield_message
 * @brief Handle text name of actor
 */
class Textfield_message : public QGraphicsTextItem {
public:

    /**
     * @param string Initial string
     * @param p Message parent
     */
    Textfield_message(const QString &string, QGraphicsItem *p);

    /**
     * @brief Centre position of text on new text
     */
    void set_pos();

    QString old_string;

    /**
     * @brief Call set_pos() to centre text
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    /**
     * @brief Message parent
     */
    QGraphicsItem *parent;
};

/**
 * @class Message
 * @brief Represents Message of class
 */
class Message : public QGraphicsLineItem {
public:
    /**
     * @param parent1 Actor or Object parent
     * @param parent2 Actor or Object parent
     * @param len Len from entity on Lifeline
     * @param isDashed bool if it's dashed line
     * @param isBlackArrow bool if it's black arrow
     * @param isCreated bool if it's create message
     * @param n Name of message
     */
    Message(QGraphicsRectItem *parent1, QGraphicsRectItem *parent2, qreal len, bool isDashed,
            bool isBlackArrow, bool isCreated, const QString &n);

    QGraphicsRectItem *parent_from;
    QGraphicsRectItem *parent_to;
    bool is_dashed;
    bool is_black;
    bool is_created;
    Textfield_message *name = nullptr;

    /**
     * @brief Handle collect data of Message into json
     * @return Json object with data
     */
    QJsonObject *get_message_data();

    /**
     * @param entity Represents Actor or Object
     * @return Name of Actor or Object
     */
    static QString get_name(QGraphicsItem *entity);

private:

    Point *p1;
    Point *p2;
};


#endif //DIAGRAM_EDITOR_MESSAGE_H
