/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file canvas.h
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QObject>
#include <QToolBox>
#include "src/gui/canvas/class-diagram/entity/entity.h"
#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"
#include "src/gui/canvas/sequence-diagram/object/object.h"
#include "src/gui/canvas/sequence-diagram/message/message.h"

class Side_toolbox;

class Class_diagram;

/**
 * @class Canvas
 * @brief Class represents view and scene where diagrams are draw
 */
class Canvas : public QGraphicsView {
public:
    QGraphicsScene *scene;
    Side_toolbox *side_toolbox;
    Class_diagram *class_diagram;
    Sequence_diagram *sequence_diagram;
    qreal scene_scale;

    /**
     * @brief Constructor
     * @param parent
     */
    Canvas(Side_toolbox *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~Canvas();

    /**
     * @brief Get class Class_diagram
     * @return pointer to class Class_diagram
     */
    Class_diagram *get_class_diagram();

    /**
     * @brief Get class Sequence_diagram
     * @return pointer to Sequence_diagram
     */
    Sequence_diagram *get_sequence_diagram();

    /**
     * Get scene
     * @return scene pointer
     */
    QGraphicsScene *get_scene();

public slots:

    /**
     * @brief Handle when user need make items bigger in the scene
     */
    void zoom_in();

    /**
     * @brief Handle when user need make items smaller in the scene
     */
    void zoom_out();

    void update_combobox();
};

#endif // CANVAS_H
