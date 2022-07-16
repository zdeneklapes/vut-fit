/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file relation_text.h
 */

#ifndef RELATION_TEXT_H
#define  RELATION_TEXT_H

#include <QGraphicsTextItem>

class Relation_line; // forward

/************************************************************************************* NEXT_CLASS */
class Relation_text : public QGraphicsTextItem {
public:
    Relation_line *parent;
    QString text;

    /**
     * @brief Constructor
     * @param str text fot string
     * @param p where text is placed
     */
    Relation_text(const QString &str, Relation_line *p);

    /**
     * @brief Destructor
     */
    ~Relation_text();

    /**
     * @brief Handle text change
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * @brief Handle change, save text
     * @param event
     */
    void focusOutEvent(QFocusEvent *event) override;

    /**
     * @brief Set new position for text
     */
    void set_pos();

};

#endif // RELATION_TEXT_H
