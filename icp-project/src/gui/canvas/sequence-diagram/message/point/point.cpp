/**
 * @author Andrej Bínovský (xbinov00)
 * @file point.cpp
 * @copyright https://stackoverflow.com/a/32198716
 */

#include "src/gui/canvas/sequence-diagram/message/message.h"

Point::Point(const QRectF &rect, bool _isP1, QGraphicsRectItem *own_p,
             QGraphicsRectItem *neighbour_p)
        : QGraphicsEllipseItem(rect, own_p),
          own_parent(own_p),
          neighbour_parent(neighbour_p),
          isP1(_isP1) {
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    if (_isP1) {
        setFlag(QGraphicsItem::ItemIsMovable);
    } else {
        QPolygonF Triangle;
        Triangle.append(QPointF(-20., -5));
        Triangle.append(QPointF(-20., 5));
        Triangle.append(QPointF(0, 0));
        Triangle.append(QPointF(0, 0));
        arrow = new QGraphicsPolygonItem(Triangle, this);
        arrow->setPos(rect.x(), rect.y());
    }
    setData(0, "point");

}

Point::~Point() {
    if ((isP1 ? neighbour_point->arrow : arrow) != nullptr) {
        delete (isP1 ? neighbour_point->arrow : arrow);
        (isP1 ? neighbour_point->arrow : arrow) = nullptr;
        delete neighbour_point;
        delete line;
    }
}

void Point::addLine(QGraphicsLineItem *l) {
    this->line = l;
}

QVariant Point::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange and isSelected()) {
        auto new_pos_y = value.toPointF().y();

        auto p1_parent = isP1 ? own_parent : neighbour_parent;
        auto p2_parent = isP1 ? neighbour_parent : own_parent;

        auto start_scene_lifeline_y_p1 =
                p1_parent->scenePos().y() + p1_parent->boundingRect().height();
        auto start_scene_lifeline_y_p2 =
                p2_parent->scenePos().y() + p2_parent->boundingRect().height();
        auto start_len_from_lifetime = line->data(1).toDouble();

        QPointF p1 = QPointF(line->line().p1().x(),
                             start_len_from_lifetime + start_scene_lifeline_y_p1 + new_pos_y);
        QPointF p2 = QPointF(line->line().p2().x(),
                             start_len_from_lifetime + start_scene_lifeline_y_p2 + new_pos_y);
        line->setLine(QLineF(p1, p2));
        neighbour_point->setPos(neighbour_point->pos().x(), new_pos_y);

        line->setData(2, start_len_from_lifetime + new_pos_y);
        ((Message *) line)->name->set_pos();
        return QPointF(pos().x(), value.toPointF().y());

    }
    if (change == ItemScenePositionHasChanged and !isSelected()) {
        QPointF newPos = value.toPointF();
        auto xOffset = rect().x() + rect().width() / 2;
        auto yOffset = rect().y() + rect().height() / 2;

        QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);
        QPointF p1 = isP1 ? newCenterPos : line->line().p1();
        QPointF p2 = isP1 ? line->line().p2() : newCenterPos;
        line->setLine(QLineF(p1, p2));
        ((Message *) line)->name->set_pos();
        rotate_arrow();
    }

    return QGraphicsItem::itemChange(change, value);
}

void Point::rotate_arrow() {
    QTransform transform;
    auto diff = own_parent->boundingRect().height() - neighbour_parent->boundingRect().height();
    auto angle = qRadiansToDegrees(
            qAtan2(scenePos().y() - neighbour_point->scenePos().y() + diff,
                   scenePos().x() - neighbour_point->scenePos().x())
    );
    angle += isP1 ? 180 : 0;
    transform.rotate(angle, Qt::ZAxis);
    isP1 ? neighbour_point->arrow->setTransform(transform) : arrow->setTransform(transform);
}
