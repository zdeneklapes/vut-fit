/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file canvas.cpp
 */

#include "src/gui/canvas/canvas.h"
#include "src/gui/side-toolbox/side_toolbox.h" // forwarding
#include "src/gui/canvas/class-diagram/class_diagram.h" // forwarding

Canvas::Canvas(Side_toolbox *parent)
        : QGraphicsView(parent),
          scene(new QGraphicsScene(this)),
          side_toolbox(parent),
          class_diagram(new Class_diagram(scene, parent)),
          sequence_diagram(new Sequence_diagram(scene)),
          scene_scale(1) {
    /* scene */
    scene->setBackgroundBrush(Qt::NoBrush);
    setScene(scene);

    /* view */
    setScene(scene);
    setBackgroundBrush(Qt::white);
    setDragMode(QGraphicsView::RubberBandDrag);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    this->scale(1, 1);
    connect(scene, &QGraphicsScene::selectionChanged, this, &Canvas::update_combobox);
}

void Canvas::update_combobox() {
    for (const auto &item: scene->selectedItems()) {
        if (item->data(0).toString() == "relation_line") {
            const auto line = (Relation_line *) item;
            const auto t1 = line->type1;
            const auto t2 = line->type2;
            if (t1 == Relation_line::ASSOCIATION) { side_toolbox->p1_combo_box->setCurrentIndex(0); }
            if (t1 == Relation_line::AGGREGATION) { side_toolbox->p1_combo_box->setCurrentIndex(1); }
            if (t1 == Relation_line::COMPOSITION) { side_toolbox->p1_combo_box->setCurrentIndex(2); }
            if (t1 == Relation_line::GENERALIZATION) { side_toolbox->p1_combo_box->setCurrentIndex(3); }
            if (t2 == Relation_line::ASSOCIATION) { side_toolbox->p2_combo_box->setCurrentIndex(0); }
            if (t2 == Relation_line::AGGREGATION) { side_toolbox->p2_combo_box->setCurrentIndex(1); }
            if (t2 == Relation_line::COMPOSITION) { side_toolbox->p2_combo_box->setCurrentIndex(2); }
            if (t2 == Relation_line::GENERALIZATION) { side_toolbox->p2_combo_box->setCurrentIndex(3); }
        }
    }
}

void Canvas::zoom_in() {
    if (scene_scale < 1) {
        scene_scale = 1;
    }
    scene_scale += 0.1;
    this->scale(scene_scale, scene_scale);
}

void Canvas::zoom_out() {
    if (scene_scale > 1) {
        scene_scale = 1;
    }
    scene_scale -= 0.1;
    this->scale(scene_scale, scene_scale);
}

Canvas::~Canvas() = default;

Class_diagram *Canvas::get_class_diagram() { return class_diagram; }


Sequence_diagram *Canvas::get_sequence_diagram() { return sequence_diagram; }

QGraphicsScene *Canvas::get_scene() { return scene; }
