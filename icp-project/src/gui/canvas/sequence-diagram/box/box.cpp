/**
 * @author Andrej Bínovský (xbinov00)
 * @file box.cpp
 */

#include "src/gui/canvas/sequence-diagram/box/box.h"

Box::Box(qreal y, qreal s, Lifeline *p) : QGraphicsRectItem(0, 0, 40, s, p) {

    auto pos_y = y;
    if (y == 0) {
        pos_y = p->boundingRect().y() + 30;
    }
    setPos(p->boundingRect().center().x() - QGraphicsRectItem::boundingRect().width() / 2, pos_y);
    setBrush(Qt::red);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsScenePositionChanges |
             QGraphicsItem::ItemSendsGeometryChanges);
    setData(0, "box");
    setData(1, "true");
}

void Box::resize_rect(qreal s) {
    setRect(0, 0, 40, s);
}

QVariant Box::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange) {
        if (data(1) == "true")
            return QPointF(pos().x(), value.toPointF().y());
        setData(1, "true");
    }
    return QGraphicsItem::itemChange(change, value);
}
