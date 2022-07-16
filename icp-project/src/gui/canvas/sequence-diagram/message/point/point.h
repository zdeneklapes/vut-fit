/**
 * @author Andrej Bínovský (xbinov00)
 * @file point.h
 * @copyright https://stackoverflow.com/a/32198716
 */

#include <QApplication>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtMath>

class Message;

/**
 * @class Point
 * @brief Point created for Message class. Each message has to points
 */
class Point : public QGraphicsEllipseItem {
public:
    /**
     * @param rect Position and size of point
     * @param _isP1 Bool if it is first point
     * @param own_p Actor or Object parent
     * @param neighbour_p Actor or Object parent of second point of Message (line)
     */
    Point(
            const QRectF &rect,
            bool _isP1,
            QGraphicsRectItem *own_p = nullptr,
            QGraphicsRectItem *neighbour_p = nullptr
    );

    ~Point();

    /**
     * @brief Add line (Message) to point
     * @param line Message
     */
    void addLine(QGraphicsLineItem *line);

    /**
     * @brief Rotate arrow of line based on angle of line
     */
    void rotate_arrow();

    /**
     * @brief Handle new position of point
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    Point *neighbour_point;
    QGraphicsPolygonItem *arrow;
    QGraphicsLineItem *line;


private:
    QGraphicsRectItem *own_parent;
    QGraphicsRectItem *neighbour_parent;
    bool isP1;
};
