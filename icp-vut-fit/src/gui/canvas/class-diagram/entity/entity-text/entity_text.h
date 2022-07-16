/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file entity_text.h
 */

#ifndef ENTITY_TEXT_H
#define  ENTITY_TEXT_H

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"

class Entity; // forward
class Window; // forward
class Cmd_text_changed_entity; // forward

/**
 * @class Entity_text
 * @brief Class represents text field in class entity and inherits from QGraphicsTextItem
 */
class Entity_text : public QGraphicsTextItem {
public:
    /**
     * @brief Constructor
     * @param str initial string
     * @param p parent
     */
    Entity_text(const QString &str, Entity *p = nullptr);

    /**
     * @brief Destructor
     */
    ~Entity_text();

protected:
    Entity *parent;

    /**
     * @brief Set new position for QGraphicsTextItem
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * @brief Update changes in structure Class_info
     * @param event
     */
    void focusOutEvent(QFocusEvent *event) override;
};

#endif  // ENTITY_TEXT_H
