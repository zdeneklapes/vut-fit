/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file text_item.h
 */

#ifndef TEXT_H
#define TEXT_H

#include <QGraphicsTextItem>
#include <QString>
#include <QJsonObject>
#include <QDebug>

/**
 * @class Text_item
 * @brief
 */
class Text_item : public QGraphicsTextItem {
public:
    QString *text;

    /**
     * @brief COnstructor
     * @param str
     */
    Text_item(const QString &str = "text");

    /**
     * @brief Destructor
     */
    ~Text_item();

    /**
     * Getting json object when saving file
     * @return QJsonObject
     */
    QJsonObject *get_text_item_info();

};

#endif
