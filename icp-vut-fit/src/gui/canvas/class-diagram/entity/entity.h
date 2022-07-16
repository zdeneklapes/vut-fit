/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file entity.h
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <QDebug>
#include <QList>
#include <QRect>
#include <QString>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QJsonObject>
#include <QJsonArray>
#include <QUndoCommand>
#include "src/gui/canvas/class-diagram/entity/class_info/class_info.h"
#include "src/gui/canvas/class-diagram/entity/entity-text/entity_text.h"
#include "src/gui/canvas/class-diagram/undo-redo/undo_redo.h"

class Entity_text; // forwarding


/**
 * @class Entity
 * @brief Class that represents entity in class diagram and inherits form QGraphicsRectItem
 */
class Entity : public QGraphicsRectItem {
public:
    Class_info *class_info;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

    /**
     * @brief Constructor
     * @param scene scene where class will be placed
     * @param info class data (optional)
     */
    Entity(QGraphicsScene *scene, Class_info *info = new Class_info());

    /**
     * @brief Destructor
     */
    ~Entity();

    /**
     * @brief Calculate new boundingRect based on all child Text_items
     * @param entity (optional)
     * @return new QRect for class
     */
    QRect refactor_rect(Entity *entity = nullptr);

    /**
     * @brief Getting json object when saving file
     * @return QJsonObject
     */
    QJsonObject *get_entity_info();

    /**
     * @brief Remove all child Text_items
     */
    void remove_elements();

    /**
     * @brief Create Text_items and set parent to entity object
     */
    void create_elements();

    /**
     * @brief Get all Entity_text child in entity
     * @param entity where search for child
     * @return QList with child
     */
    QList<Entity_text *> *get_text_item_child(Entity *entity);

    /**
     * @brief update separators when rect size changed
     */
    void update_separator();

    /**
     * @brief Update all element in class
     */
    void update_elements();

protected:
    QGraphicsScene *parent;

    /**
     * @brief Calculate new posiiton for Text_item in entity rectangle
     * @return int new y position
     */
    int new_y_text_item();

    /**
     * @brief Handle change event
     * @param change
     * @param value
     * @return
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    /**
     * @brief Create lines between name,attributes and methods
     * @param text
     */
    void create_separator(Entity_text *text);
};

#endif  // ENTITY_H
