/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file relation_point.h
 */

#ifndef RELATION_POINT_H
#define RELATION_POINT_H

#include <QGraphicsEllipseItem>
#include "src/gui/canvas/class-diagram/entity/entity.h"

class Relation_line; // forwarding

/**
 * @class Relation_point
 * @brief Class is used as point for line
 */
class Relation_point : public QGraphicsEllipseItem {
public:
    Relation_line *line;

    /**
     * @brief Constructor
     * @param Relation_line into which line it point belong
     * @param Entity parent
     */
    Relation_point(Relation_line *, Entity *);

    /**
     * @brief Destructor
     */
    ~Relation_point();

private:
    /**
     * @brief Handle change
     * @param change
     * @param value
     * @return
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // RELATION_POINT_H
