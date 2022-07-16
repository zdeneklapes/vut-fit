/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file class_diagram.h
 */

#ifndef CLASS_DIAGRAM_H
#define CLASS_DIAGRAM_H

#include <functional>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QPushButton>
#include <QLayoutItem>
#include <QObject>
#include <QFont>
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QTableWidget>
#include "src/gui/canvas/class-diagram/entity/entity.h"
#include "src/gui/canvas/class-diagram/undo-redo/undo_redo.h"
#include "src/gui/canvas/class-diagram/relation/relation_line.h"
#include "src/gui/canvas/class-diagram/relation/relation-point/relation_point.h"
#include "src/gui/window.h"
#include "src/gui/canvas/class-diagram/text-item/text_item.h"

class Side_toolbox; // forwarding

/**
 * @class Class_diagram
 * @brief Class that serves to handle class diagram operations, like creating entities etc...
 */
class Class_diagram : public QObject {
    QOBJECT_H
public:
    QGraphicsScene *scene;

    /**
     * @brief Constructor
     * @param scene where diagram is placed
     * @param side_toolbox_
     */
    Class_diagram(QGraphicsScene *scene, Side_toolbox *side_toolbox_);

    /**
     * @brief Destructor
     */
    ~Class_diagram();

    /**
     * @brief Handle pushbutton and insert text item into scene
     */
    void add_text_item();

public slots:

    /**
     * @brief create new entity in teh scene
     */
    void add_class();

    /**
     * @brief Delete selected classes
     */
    void delete_class();

    /**
     * @brief Add new attribute to class behind selected attribute
     */
    void add_attribute();

    /**
     * @brief Delete selected attribute
     */
    void delete_attribute();

    /**
     * @brief Add new method to class behind selected method
     */
    void add_method();

    /**
     * @brief Delete selected method
     */
    void delete_method();

    /**
     * @brief Connect 2 selected classes
     */
    void connect_classes();

    /**
     * @brief Delete selected connection
     */
    void disconnect_classes();

    /**
     * @brief Change relation type
     * @param text
     */
    void update_connection(const QString &text);

    /**
     * @brief Check if item in the scene is object of class Entity
     * @param item
     * @return bool
     */
    static bool is_entity(const QGraphicsItem *item);

    /**
     * @brief Check if item in the scene is object of class Text_item
     * @param item
     * @return bool
     */
    static bool is_text_item(const QGraphicsItem *item);

    /**
     * @brief Check if item in the scene is object of class Relation_point
     * @param item
     * @return bool
     */
    static bool is_relation_point(const QGraphicsItem *item);

    /**
     * @brief From child retrieve object of class Entity
     * @return Entity* (child parent)
     */
    Entity *get_entity_from_child();

    /**
     * @brief Get object of class Entity by name, from item in the scene
     * @param name
     * @param scene
     * @return Entity* (find by name in the scene)
     */
    static Entity *get_entity_by_name(const QString &name, QGraphicsScene *scene);

    /**
     * @brief Run lambda functions inserted as function argument
     * @param cb_cond
     * @param cb_func
     */
    void run_selected(
            const std::function<bool(Entity_text *child_, const int idx,
                                     Entity *entity)> &cb_cond,
            const std::function<void(Entity_text *child_, const int idx, Entity *entity)> &cb_func);

    /**
     * @brief Return selected object in the scene of class Entity
     * @return QList
     */
    QList<Entity *> *get_selected_entities();


    /**
     * @brief  Get selected line
     * @return  Return selected line from the scene (must selected only one item in the scene)
     */
    Relation_line *get_relation_line();

    /**
     * @brief Sequence diagram call this method when class name changed
     * @param s
     * @param old_string
     * @param new_string
     */
    static void
    change_class_name(QGraphicsScene *s, const QString &old_string, const QString &new_string);

    /**
     * @brief Sequence diagram call this method when method in class change
     * @param s
     * @param entity_name
     * @param old_string
     * @param new_string
     */
    static void
    change_class_method(QGraphicsScene *s, const QString &entity_name, const QString &old_string,
                        const QString &new_string);

    /**
     * @brief Delete selected Text_item from scene
     */
    void delete_text_item();

private:
    Side_toolbox *side_toolbox;

//    Relation_line::Type get_types_from_combobox(int num);

    void create_connection(QList<Entity *> *rects, const QString &name);
};

#endif // CLASS_DIAGRAM_H
