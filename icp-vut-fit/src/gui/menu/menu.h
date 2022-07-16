/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file menu.h
 */

#ifndef MENU_H
#define MENU_H

// QT
#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTranslator>
#include <QMessageBox>
#include <QDialog>
#include <QScrollArea>
#include <QScrollBar>

#include "src/core/open-file/open_file.h"
#include "src/core/save-file/save_file.h"
#include "src/gui/side-toolbox/side_toolbox.h"
#include "src/gui/canvas/canvas.h"

// forward
class Window;

class Side_toolbox;

class Menu : public QMenuBar {
public:
    QMenu *file_menu;
    QMenu *help_menu;
    Side_toolbox *side_toolbox;
    QAction *help_act;
    QAction *open_file_act;
    QAction *save_file_act;
    QAction *undo_act;
    QAction *zoom_in_act;
    QAction *zoom_out_act;
    Canvas *canvas;

    /**
     * @brief Constructor
     * @param parent
     * @param c
     */
    Menu(Window *parent = nullptr, Canvas *c = nullptr);

    /**
     * @brief Destructor
     */
    ~Menu();

public slots:

    /**
     * @brief Undo scene operations
     */
    void undo();

    /**
     * Show help dialog
     */
    void help();

private:
    /**
     * @brief Create action in menu
     */
    void create_actions();

    /**
     * @brief Create menu with all buttons
     */
    void create_menu();
};

#endif  // MENU_H
