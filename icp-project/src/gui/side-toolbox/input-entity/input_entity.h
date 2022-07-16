/**
 * @author Andrej Bínovský (xbinov00)
 * @file input_entity.h
 */

#ifndef DIAGRAM_EDITOR_INPUT_ENTITY_H
#define DIAGRAM_EDITOR_INPUT_ENTITY_H

#include <QLineEdit>
#include <QDebug>

/**
 * @class Input_entity
 * @brief Input entity represents QLineEdit for 3 instances
 */
class Input_entity : public QObject {
public:
    /**
     * @param _input_flag Represents flag of calling instance
     */
    Input_entity(int _input_flag);

    /**
     * @brief QLineEdit
     */
    QLineEdit *input;

    /**
     * @brief Represents flag of calling instance
     */
    int input_flag;

    /**
     * @brief Value of input
     */
    static QString entity_from;

    /**
    * @brief Value of input
    */
    static QString entity_to;

    /**
    * @brief Value of input
    */
    static QString diagram_name;

public slots:

    /**
    * @brief Slot handle change of changed value of input
    */
    void handle_change();
};


#endif //DIAGRAM_EDITOR_INPUT_ENTITY_H
