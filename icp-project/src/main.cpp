/**
 * @author Zdeněk Lapeš (xlapes02)
 * @author Andrej Bínovský (xbinov00)
 * @file main.cpp
 */
#include <QApplication>
#include <iostream>
#include "src/gui/window.h"

/**
 * @brief Here application starts
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
