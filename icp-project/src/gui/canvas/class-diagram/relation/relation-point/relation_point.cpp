/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file relation_point.cpp
 */

#include "src/gui/canvas/class-diagram/relation/relation-point/relation_point.h"
#include "src/gui/canvas/class-diagram/relation/relation_line.h" // forwarding

Relation_point::Relation_point(Relation_line *line_, Entity *parent)
        : QGraphicsEllipseItem(0, 0, 1, 1, parent), line(line_) {
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setData(0, "relation_point");
}

QVariant Relation_point::itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant &value) {
    if (change == ItemScenePositionHasChanged && scene()) {
        line->set_positions();
        line->update_text_pos();
    }
    return QGraphicsItem::itemChange(change, value);
}

Relation_point::~Relation_point() = default;
