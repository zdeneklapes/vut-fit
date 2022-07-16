/**
 * @author Andrej Bínovský (xbinov00)
 * @file actor.h
 */

#ifndef DIAGRAM_EDITOR_ACTOR_H
#define DIAGRAM_EDITOR_ACTOR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>

#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"

class Class_diagram;

/**
 * @class Textfield_actor
 * @brief Handle text name of actor
 */
class Textfield_actor : public QGraphicsTextItem {
public:

    /**
     * @param string Initial string
     * @param p Actor parent
     */
    Textfield_actor(const QString &string, QGraphicsItem *p);

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
     * @brief Actor parent
     */
    QGraphicsItem *parent;
};

/**
 * @class Actor
 * @brief Create graphics item, which representing Actor
 */
class Actor : public QGraphicsRectItem {
public:
    /**
     * @param x Position of actor (x)
     * @param y Position of actor (y)
     * @param s Size of actor. Width and height
     * @param n String name of Actor
     */
    Actor(qreal x, qreal y, qreal s, const QString &n);

    /**
     * @brief Sets position of body
     */
    void set_body();

    /**
     * @brief Handle collect data of Actor into json
     * @return Json object with data
     */
    QJsonObject *get_actor_data();

    qreal size;
    Textfield_actor *name;
    Lifeline *lifeline;
private:
    QGraphicsEllipseItem *head;
    QGraphicsLineItem *body;
    QGraphicsLineItem *hands;
    QGraphicsLineItem *left_leg;
    QGraphicsLineItem *right_leg;
};

#endif //DIAGRAM_EDITOR_ACTOR_H
