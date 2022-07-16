/**
 * @author Andrej Bínovský (xbinov00)
 * @file sequence_diagram.h
 */

#ifndef DIAGRAM_EDITOR_SEQUENCE_DIAGRAM_H
#define DIAGRAM_EDITOR_SEQUENCE_DIAGRAM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QMap>
#include <QDebug>
#include <QJsonObject>

#include "src/gui/canvas/sequence-diagram/actor/actor.h"
#include "src/gui/canvas/sequence-diagram/object/object.h"
#include "src/gui/canvas/sequence-diagram/box/box.h"
#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"
#include "src/gui/canvas/sequence-diagram/message/message.h"
#include "src/gui/side-toolbox/input-entity/input_entity.h"

/**
 * @class Sequence_diagram
 * @brief Connects all canvas items view QGraphicsView
 */
class Sequence_diagram : public QObject {
public:
    /**
     * @param scene Scene of QGraphicsView
     */
    Sequence_diagram(QGraphicsScene *scene);

    /**
     * @brief Create new Message
     * @param is_dashed bool
     * @param is_black_arrow bool
     * @param is_created bool
     */
    void create_message(bool is_dashed, bool is_black_arrow, bool is_created);

    Input_entity *input_diagram_name = nullptr;
public slots:

    /**
     * @brief Delete selected item
     */
    void delete_items();

    /**
     * @brief Delete entities of scene by name
     * @param s QGraphicsScene
     * @param name Name of entity
     */
    static void delete_entities(QGraphicsScene *s, const QString &name);

    /**
     * @brief Delete all children of selected item
     * @param children
     */
    static void delete_children(const QList<QGraphicsItem *> &children);

    /**
     * @brief Create new Actor
     */
    void create_actor();

    /**
     * @brief Create new Object
     */
    void create_object();

    /**
    * @brief Create new Box
    */
    void create_box();

    /**
    * @brief Create new synchronous Message
    */
    void create_message_sync();

    /**
    * @brief Create new asynchronous Message
    */
    void create_message_async();

    /**
    * @brief Create new <<create>> message
    */
    void create_message_create();

    /**
    * @brief Create new asynchronous return / reply
    */
    void create_message_async_return();

    /**
     * @brief Set sequence diagram name from selected item
     */
    void set_diagram();

    /**
     * @brief Replace old name of entity (Actor of Object) by new one.
     * @param s QGraphicsScene
     * @param old_string
     * @param new_string
     */
    static void
    change_entity_name(QGraphicsScene *s, const QString &old_string, const QString &new_string);

    /**
     * @brief Replace old name of message by new one.
     * @param s QGraphicsScene
     * @param old_string
     * @param new_string
     * @param entity_name Name of entity which own message
     */
    static void
    change_message_name(QGraphicsScene *s, const QString &old_string, const QString &new_string,
                        const QString &entity_name);

private:
    QGraphicsScene *scene;
};

#endif //DIAGRAM_EDITOR_SEQUENCE_DIAGRAM_H
