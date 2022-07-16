/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file relation_line.h
 */

#ifndef DIAGRAM_EDITOR_RELATION_LINE_H
#define DIAGRAM_EDITOR_RELATION_LINE_H

#include <QGraphicsLineItem>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QGraphicsRectItem>
#include <QtMath>
#include <QLine>
#include "src/gui/canvas/class-diagram/entity/entity.h"
#include "src/gui/canvas/class-diagram/relation/relation-text/relation_text.h"

class Relation_point;

class Relation_line : public QGraphicsLineItem {
public:
    enum Type {
        ASSOCIATION, AGGREGATION, COMPOSITION, GENERALIZATION
    };
    Entity *entity1;
    Entity *entity2;

    Type type1 = ASSOCIATION;
    Type type2 = ASSOCIATION;

    Relation_point *relation_point1 = nullptr;
    Relation_point *relation_point2 = nullptr;

    QGraphicsPolygonItem *type_point1 = nullptr;
    QGraphicsPolygonItem *type_point2 = nullptr;

    Relation_text *name;

    /**
     * @brief Constructor
     * @param entity1_ first point for line
     * @param entity2_ second point for line
     * @param type1_ Type for point
     * @param type2_ Type for point
     * @param name_ relation name
     */
    Relation_line(Entity *entity1_, Entity *entity2_, Relation_line::Type type1_,
                  Relation_line::Type type2_, const QString &name_);

    /**
     * @brief Destructor
     */
    ~Relation_line();

    /**
     * @brief Set points position
     */
    void set_positions();

    /**
     * @brief Delete points
     */
    void delete_points() const;

    /**
     *  @brief Set new text position
     */
    void update_text_pos() const;

    /**
     * @brief Get info about line, points, and texts
     * @return QJsonObject
     */
    QJsonObject *get_relation_line_info();

    /**
     * @brief Get relation type as tring
     * @param type_number int
     * @return QString relation type
     */
    QString get_relation_type(int type_number) const;

    /**
     * @brief Get relation type as enum Type
     * @param name name of type
     * @return enum Type
     */
    static Type get_relation_type(const QString &name);

    /**
     * @brief Count angle for two points
     * @return Double angle
     */
    double get_angle() const;

    /**
     * @brief Check if angle is between specified values
     * @param start angle start
     * @param end angle end
     * @param angle angle
     * @return true if angle is between start and end values
     */
    bool is_between_degrees(int start, int end, int angle);

private:
    /**
     * @brief Set new position for points and line
     * @param p1 point of entity1 for new point position
     * @param p2 point of entity2 for new point position
     */
    void set_points_and_line_pos(QPointF p1, QPointF p2);

    /**
     * @brief Count new transformation when entities moving and point types must be rotate
     * @param type_point
     * @param is_type1
     * @return QTransform
     */
    QTransform transform_type(QGraphicsPolygonItem *type_point, bool is_type1);

    /**
     * @brief Initialize points type
     */
    void init_point_types();
};

#endif //DIAGRAM_EDITOR_RELATION_LINE_H
