/**
 * @author Andrej Bínovský (xbinov00)
 * @file box.h
 */

#ifndef DIAGRAM_EDITOR_BOX_H
#define DIAGRAM_EDITOR_BOX_H

#include <QGraphicsItem>
#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"

/**
 * @class Box
 * @brief Represents time entity existence
 */
class Box : public QGraphicsRectItem {
public:
    /**
     * @param y Position on lifeline (x is not needed, its from lifeline)
     * @param s Size of Box - height
     * @param p Lifeline parent
     */
    Box(qreal y, qreal s, Lifeline *p);

    /**
     * @brief Method is for box changing position
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    /**
     * Method is for resizing Box
     * @param s New height of Box
     */
    void resize_rect(qreal s);
};

#endif //DIAGRAM_EDITOR_BOX_H
