/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file relation_line.cpp
 */

#include "src/gui/canvas/class-diagram/relation/relation-point/relation_point.h"
#include "src/gui/canvas/class-diagram/relation/relation-point/relation_point.h" // forward

Relation_line::Relation_line(Entity *entity1_, Entity *entity2_, Relation_line::Type type1_,
                             Relation_line::Type type2_, const QString &name_)
        : QGraphicsLineItem(0, 0, 0, 0),
          entity1(entity1_), entity2(entity2_),
          type1(type1_), type2(type2_),
          relation_point1(new Relation_point(this, entity1)),
          relation_point2(new Relation_point(this, entity2)),
          name(new Relation_text(name_, this)) {
    setFlags(QGraphicsLineItem::ItemIsSelectable);
    setData(0, "relation_line");
    init_point_types();
    set_positions();
    setZValue(-1);
    update_text_pos();
}

void Relation_line::init_point_types() {
    QRectF rect_polygon(0, 0, 10, 10);
    QVector<QPointF> vector;
    vector.push_back(QPointF(0, 0));
    vector.push_back(QPointF(10, 0));
    vector.push_back(QPointF(0, 10));
    if (type1 == AGGREGATION) {
        type_point1 = new QGraphicsPolygonItem(QPolygonF(rect_polygon), relation_point1);
        type_point1->setBrush(Qt::white);
    } else if (type1 == COMPOSITION) {
        type_point1 = new QGraphicsPolygonItem(QPolygonF(rect_polygon), relation_point1);
        type_point1->setBrush(Qt::black);
    } else if (type1 == GENERALIZATION) {
        type_point1 = new QGraphicsPolygonItem(QPolygonF(vector), relation_point1);
        type_point1->setBrush(Qt::white);
    }

    if (type2 == AGGREGATION) {
        type_point2 = new QGraphicsPolygonItem(QPolygonF(rect_polygon), relation_point2);
        type_point2->setBrush(Qt::white);
    } else if (type2 == COMPOSITION) {
        type_point2 = new QGraphicsPolygonItem(QPolygonF(rect_polygon), relation_point2);
        type_point2->setBrush(Qt::black);
    } else if (type2 == GENERALIZATION) {
        type_point2 = new QGraphicsPolygonItem(QPolygonF(vector), relation_point2);
        type_point2->setBrush(Qt::white);
    }

    if (type_point1) type_point1->setZValue(1);
    if (type_point2) type_point2->setZValue(1);
}

void Relation_line::set_positions() {
    // tmp_vars
    const auto e1 = entity1->boundingRect();
    const auto e2 = entity2->boundingRect();
    const auto p1 = relation_point1->boundingRect();
    const auto p2 = relation_point2->boundingRect();
    const auto p1_centre = QPointF(p1.width() / 2, p1.height() / 2);
    const auto p2_centre = QPointF(p2.width() / 2, p2.height() / 2);

    // corners
    auto e1_c_t_l = QPointF(e1.x(), e1.y()) - p1_centre;
    auto e1_c_t_r = QPointF(e1.x() + e1.width(), e1.y()) - p1_centre;
    auto e1_c_b_r = QPointF(e1.x() + e1.width(), e1.y() + e1.height()) - p1_centre;
    auto e1_c_b_l = QPointF(e1.x(), e1.y() + e1.height()) - p1_centre;

    // corners
    auto e2_c_t_l = QPointF(e2.x(), e2.y()) - p2_centre;
    auto e2_c_t_r = QPointF(e2.x() + e2.width(), e2.y()) - p2_centre;
    auto e2_c_b_r = QPointF(e2.x() + e2.width(), e2.y() + e2.height()) - p2_centre;
    auto e2_c_b_l = QPointF(e2.x(), e2.y() + e2.height()) - p2_centre;

    auto degree_point = [](int i) { return i * 90; };

    // TRANSFORM
    if (type_point1) type_point1->setTransform(transform_type(type_point1, true));
    if (type_point2) type_point2->setTransform(transform_type(type_point2, false));

    if (is_between_degrees(degree_point(0), degree_point(1), (int) get_angle())) {
        set_points_and_line_pos(e1_c_t_r, e2_c_b_l);
    } else if (is_between_degrees(degree_point(1), degree_point(2), (int) get_angle())) {
        set_points_and_line_pos(e1_c_t_l, e2_c_b_r);
    } else if (is_between_degrees(degree_point(-2), degree_point(-1), (int) get_angle())) {
        set_points_and_line_pos(e1_c_b_l, e2_c_t_r);
    } else if (is_between_degrees(degree_point(-1), degree_point(0), (int) get_angle())) {
        set_points_and_line_pos(e1_c_b_r, e2_c_t_l);
    }
}

double Relation_line::get_angle() const {
    return qRadiansToDegrees(qAtan2(entity1->y() - entity2->y(), entity2->x() - entity1->x()));
}

bool Relation_line::is_between_degrees(int start, int end, int angle) {
    return start < angle && angle <= end;
}


void Relation_line::delete_points() const {
    delete relation_point1; // delete type_point1 as well, because parent
    delete relation_point2; // delete type_point2 as well, because parent
}

QTransform
Relation_line::transform_type([[maybe_unused]]QGraphicsPolygonItem *type_point, bool is_type1) {
    QTransform transform;
    auto angle = qRadiansToDegrees(
            qAtan2(relation_point1->scenePos().y() - relation_point2->scenePos().y(),
                   relation_point1->scenePos().x() - relation_point2->scenePos().x())
    );
    angle += is_type1 ? 45 * 3 : -45;
    transform.translate(-type_point->boundingRect().x(), -type_point->boundingRect().y());
    transform.rotate(angle, Qt::ZAxis);
    transform.translate(+type_point->boundingRect().x(), +type_point->boundingRect().y());
    return transform;
}

void Relation_line::set_points_and_line_pos(QPointF p1, QPointF p2) {
    relation_point1->setPos(p1);
    relation_point2->setPos(p2);
    setLine(QLineF(entity1->pos() + p1, entity2->pos() + p2));
}

QJsonObject *Relation_line::get_relation_line_info() {
    auto relation = new QJsonObject;
    // entities
    relation->insert("entity1", QJsonValue::fromVariant(this->entity1->class_info->name));
    relation->insert("entity2", QJsonValue::fromVariant(this->entity2->class_info->name));
    // text
    relation->insert("name", QJsonValue::fromVariant(this->name->toPlainText()));
    // types
    relation->insert("type1", QJsonValue::fromVariant(this->get_relation_type(1)));
    relation->insert("type2", QJsonValue::fromVariant(this->get_relation_type(2)));
    return relation;
}


QString Relation_line::get_relation_type(int type_number) const {
    if (type_number == 1) {
        switch (type1) {
            case ASSOCIATION:
                return "ASSOCIATION";
            case AGGREGATION:
                return "AGGREGATION";
            case COMPOSITION:
                return "COMPOSITION";
            case GENERALIZATION:
                return "GENERALIZATION";
            default:
                return "";
        }
    } else {
        switch (type2) {
            case ASSOCIATION:
                return "ASSOCIATION";
            case AGGREGATION:
                return "AGGREGATION";
            case COMPOSITION:
                return "COMPOSITION";
            case GENERALIZATION:
                return "GENERALIZATION";
            default:
                return "";
        }
    }
}

Relation_line::Type Relation_line::get_relation_type(const QString &name) {
    if (name.toUpper() == "ASSOCIATION") return ASSOCIATION;
    else if (name.toUpper() == "AGGREGATION") return AGGREGATION;
    else if (name.toUpper() == "COMPOSITION") return COMPOSITION;
    else return GENERALIZATION;
}

void Relation_line::update_text_pos() const {
    name->set_pos();
}

Relation_line::~Relation_line() = default;

