/**
 * @author Andrej Bínovský (xbinov00)
 * @file lifeline.h
 */

#ifndef DIAGRAM_EDITOR_LIFELINE_H
#define DIAGRAM_EDITOR_LIFELINE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "src/gui/side-toolbox/input-entity/input_entity.h"

/**
 * @class Lifeline
 * @brief Represents lifeline of entity (Actor or Object)
 */
class Lifeline : public QGraphicsLineItem {
public:
    /**
     * @param x Position of Lifeline (x)
     * @param y Position of Lifeline (y)
     * @param parent Actor or Object parent
     */
    Lifeline(qreal x, qreal y, QGraphicsItem *parent = nullptr);

    /**
     * @brief Method resize length of Lifeline
     */
    void resize();

    /**
     * @return All boxes on Lifeline
     */
    QJsonArray *get_boxes();

    static QMap<QString, qreal> size;
    qreal pos_x;
    qreal pos_y;
};

#endif //DIAGRAM_EDITOR_LIFELINE_H
