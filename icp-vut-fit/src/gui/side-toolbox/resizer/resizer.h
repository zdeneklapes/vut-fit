/**
 * @author Andrej Bínovský (xbinov00)
 * @file resizer.h
 */

#ifndef DIAGRAM_EDITOR_RESIZER_H
#define DIAGRAM_EDITOR_RESIZER_H

#include <QSlider>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "src/gui/canvas/sequence-diagram/box/box.h"
#include "src/gui/canvas/sequence-diagram/lifeline/lifeline.h"

/**
 * @class Resizer
 * @brief Represents slider which returns values to resize items in QGraphicsScene
 */
class Resizer : public QObject {
public:
    /**
     * @param scene QGraphicsScene with items
     */
    Resizer(QGraphicsScene *scene);

    /**
     * @brief Slider
     */
    QSlider *slider;
private:
    /**
     * @brief QGraphicsScene with items
     */
    QGraphicsScene *scene;
    /**
     * @brief Value of slider
     */
    qreal value;

    /**
     * @brief Method handle resizing length of lifeline
     */
    void lifeline();

    /**
     * @brief Method handle resizing length of box
     * @param box Object box for resize
     */
    void box(Box *box);

public slots:

    /**
     * @brief Slot handle resizing of selected item from scene
     */
    void handle_change();
};

#endif
