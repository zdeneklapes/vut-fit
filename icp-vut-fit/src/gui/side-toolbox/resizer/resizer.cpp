/**
 * @author Andrej Bínovský (xbinov00)
 * @file resizer.cpp
 */

#include "src/gui/side-toolbox/resizer/resizer.h"

Resizer::Resizer(QGraphicsScene *scene) :
        slider(new QSlider()),
        scene(scene) {

    slider->setOrientation(Qt::Horizontal);
    slider->setRange(5, 50);
    connect(slider, &QSlider::valueChanged, this, &Resizer::Resizer::handle_change);
}

void Resizer::handle_change() {
    Q_FOREACH(QGraphicsItem *item, scene->selectedItems()) {
            value = (qreal) ((QSlider *) sender())->value();
            if (item->data(0) == "lifeline" and item->parentItem()->data(10).toString() == Input_entity::diagram_name) {
                lifeline();
            } else if (item->data(0) == "box") {
                box((Box *) item);
            }
        }
}

void Resizer::box(Box *box) {
    box->resize_rect(value * 15);
}

void Resizer::lifeline() {
    Lifeline::size[Input_entity::diagram_name] = value * 20;
    Q_FOREACH(QGraphicsItem *lifeline, scene->items()) {
            if (lifeline->data(0) == "lifeline") {
                ((Lifeline *) lifeline)->resize();
            }
        }
}
