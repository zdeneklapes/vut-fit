/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file window.h
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QTranslator>
#include <QVBoxLayout>
#include <QUndoStack>
#include <QUndoCommand>
#include "src/gui/menu/menu.h"
#include "src/core/open-file/open_file.h"
#include "src/core/save-file/save_file.h"
#include "src/gui/side-toolbox/side_toolbox.h"
#include "src/gui/canvas/class-diagram/class_diagram.h"
#include "src/gui/canvas/sequence-diagram/sequence_diagram.h"

class Canvas; // forward

/***************************************************************************************************/
class Window : public QMainWindow {
Q_OBJECT
public:
    QWidget *widget;  // for setCentralWidget
    QGraphicsScene *scene;
    Side_toolbox *side_toolbox;
    Canvas *canvas;
    static QUndoStack *stack;

    /**
     * @brief Constructor
     * @param parent
     */
    Window(QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~Window();
};

#endif  // WINDOW_H
