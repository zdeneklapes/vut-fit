/**
 * @author Andrej Bínovský (xbinov00)
 * @file lifeline.cpp
 */

#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"

Lifeline::Lifeline(qreal x, qreal y, QGraphicsItem *parent) :
        QGraphicsLineItem(parent),
        pos_x(x),
        pos_y(y) {
    QPen pen;
    pen.setWidth(2);
    pen.setDashPattern({0, 1, 8, 3});
    setPen(pen);
    setLine(x, y + 30, x, y + Lifeline::size[Input_entity::diagram_name]);
    setData(0, "lifeline");
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QJsonArray *Lifeline::get_boxes() {
    auto boxes = new QJsonArray();
    Q_FOREACH(auto box, childItems()) {
            if (box->data(0) == "box") {
                auto box_json = new QJsonObject;
                box_json->insert("y", QJsonValue::fromVariant((int) box->pos().y()));
                box_json->insert("s", QJsonValue::fromVariant((int) box->boundingRect().height()));
                boxes->push_back(*box_json);
            }
        }
    return boxes;
}

void Lifeline::resize() {
    if (parentItem()->data(10).toString() == Input_entity::diagram_name)
        this->setLine(pos_x, pos_y + 30, pos_x, pos_y + Lifeline::size[Input_entity::diagram_name]);
}

QMap<QString, qreal> Lifeline::size;

