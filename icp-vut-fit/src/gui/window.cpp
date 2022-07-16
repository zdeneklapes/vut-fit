/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file window.cpp
 */
#include "src/gui/window.h"

QUndoStack *Window::stack = new QUndoStack();

#define HEIGHT 1200
#define WIDTH 700

Window::Window(QWidget *parent)
        : QMainWindow(parent),
          widget(new QWidget(this)),
          scene(new QGraphicsScene(this)),
          side_toolbox(new Side_toolbox(scene, this)) {  // must be before canvas, otherwise sig_seg
    /* layout */
    auto layout = new QHBoxLayout();
    layout->addWidget(side_toolbox, 1);
    layout->addWidget(side_toolbox->get_canvas(), 4);
    layout->setSpacing(0);

    /* window */
    widget->setLayout(layout);
    widget->setBaseSize(HEIGHT, WIDTH);
    widget->setMinimumSize(HEIGHT, WIDTH);

    this->setWindowTitle("Diagram");
    this->setMenuBar(new Menu(this, side_toolbox->get_canvas()));
    this->setCentralWidget(widget);
}

Window::~Window() {}
