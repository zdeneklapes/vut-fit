/**
 * @author Andrej Bínovský (xbinov00)
 * @file input_entity.cpp
 */

#include "src/gui/side-toolbox/input-entity/input_entity.h"

Input_entity::Input_entity(int _input_flag) : input(new QLineEdit()), input_flag(_input_flag) {
    connect(input, &QLineEdit::textChanged, this, &Input_entity::Input_entity::handle_change);
}

void Input_entity::handle_change() {
    switch (input_flag) {
        case 1:
            entity_from = ((QLineEdit *) sender())->text();
            break;
        case 2:
            entity_to = ((QLineEdit *) sender())->text();
            break;
        case 3:
            diagram_name = ((QLineEdit *) sender())->text();
            break;
    }
}

QString Input_entity::entity_from;
QString Input_entity::entity_to;
QString Input_entity::diagram_name;
