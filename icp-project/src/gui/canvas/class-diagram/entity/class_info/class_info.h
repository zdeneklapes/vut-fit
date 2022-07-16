/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file class_info.h
 */

#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <utility>
#include <QDebug>
#include <QList>
#include <QString>
#include <QLabel>
#include <QGraphicsScene>
#include <QMessageBox>

class Entity;

/**
 * @struct Element
 * @brief Struct holds information about one class
 */
struct Element {
    QString visibility;
    QString name;
    QString type;
    QString params;

    /**
     * @brief Constructor
     * @param vis initial visibility
     * @param attrib_name initial attribute name
     * @param attrib_type initial attribute type
     */
    Element(QString vis, QString attrib_name, QString attrib_type);

    /**
     * @brief Destructor
     */
    ~Element();

    /**
     * @brief From name attribute retrieve params and it into params
     */
    void update_params();
};

/************************************************************************************* NEXT_CLASS */

/**
 * Structure that hold information about whole class entity.
 * Using struct Element
 */
struct Class_info {
public:
    QString name;
    QList<Element> attributes;
    QList<Element> methods;

    /**
     * @brief Constructor
     */
    Class_info();

    /**
     * @brief Destructor
     */
    ~Class_info();

    /**
     * @brief Set class name
     * @param str new string for name
     */
    void set_name(const QString &str);

    /**
     * @brief Insert method into QList of struct Elements
     * @param at create method at index
     */
    void insert_new_method(const int at);

    /**
     * @brief Insert method into QList of struct Elements
     * @param at create method at index
     */
    void insert_method(const Element &element);

    /**
     * @brief Insert attribute into QList of struct Elements
     * @param at insert attribute at index
     */
    void insert_new_attribute(const int at);

    /**
     * @brief Insert attribute into QList of struct Elements
     * @param element insert specified element into QList attributes
     */
    void insert_attribute(const Element element);

    /**
     * @brief Update attribute at specified position to specified string
     * @param at update attribute at this index
     * @param str update attribute to str value
     * @return if str was in good format and attribute was set return true, false in any other case
     */
    bool update_attribute(const int at, const QString &str);

    /**
     * @brief Update method at specified position to specified string
     * @param at  update method at this index
     * @param str update method to str value
     * @return if str was in good format and method was set return true, false in any other case
     */
    bool update_method(const int at, const QString &str);

    /**
     * @brief Remove attribute at specified index
     * @param at index if attribute to remove
     */
    void remove_attribute(const int at);

    /**
     * @brief Remove method at specified index
     * @param at index of method to remove
     */
    void remove_method(const int at);

    /**
     * @brief Check if new method or attribute have required format
     * @param str text from QGraphicsTextItem
     * @return parsed string from QGraphicsTextItem
     */
    QStringList *verify_new_element(const QString &str);

    /**
     * @brief update class name
     * @param str
     * @return
     */
    bool update_name(const QString &str);

    /**
     * @brief Get all class names and methods from scene
     * @param scene scene where classes are placed
     * @return QMap<class name, all methods in class>
     */
    static QMap<QString, QList<QString>> *get_entities(QGraphicsScene *scene);
};

#endif
