/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file side_toolbox.h
 */

#ifndef SIDE_TOOLBOX_H
#define SIDE_TOOLBOX_H

#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QToolBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <cassert>
#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"
#include "src/gui/side-toolbox/resizer/resizer.h"
#include "src/gui/side-toolbox/input-entity/input_entity.h"

class Window; // forward
class Canvas; // forward

/**
 * @class Side_toolbox
 * @brief Create toolbox with buttons etc..., to interact with diagrams items
 */
class Side_toolbox : public QTabWidget {
Q_OBJECT

public:
    QComboBox *p1_combo_box;
    QComboBox *p2_combo_box;

    /**
     * @brief Constructor
     * @param scene
     * @param parent
     */
    Side_toolbox(QGraphicsScene *scene, Window *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~Side_toolbox();

    /**
     * @brief Create button to interact with class diagram
     * @return QWidget
     */
    QWidget *create_class_items();

    /**
     * @brief Create button to interact with sequence diagram
     * @return QWidget
     */
    QWidget *create_sequence_items();

    /**
     * @brief Get class toolbox with all buttons and combobox
     * @return
     */
    QToolBox *get_class_toolbox();

    /**
     * @brief Get sequence toolbox with all buttons and combobox
     * @return
     */
    QGraphicsScene *get_scene();

    /**
     * Get canvas with view, scene, class_diagram and sequence_diagram
     * @return
     */
    Canvas *get_canvas();

    /**
     * @brief Get value from combobox to know what type of relation should be draw
     * @param type_number what combobox
     * @return
     */
    QComboBox *get_relation_type(int type_number);

private:
    QGraphicsScene *scene;
    QToolBox *class_toolbox;
    QToolBox *sequence_toolbox;
    Canvas *canvas;

};

#endif  // SIDE_TOOLBOX_H
