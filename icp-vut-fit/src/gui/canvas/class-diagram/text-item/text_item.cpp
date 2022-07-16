/**
 * @author Zdeněk Lapeš (xlapes02)
 * @file text_item.cpp
 */

#include "src/gui/canvas/class-diagram/text-item/text_item.h"

Text_item::Text_item(const QString &str) :
        text(new QString(str)) {
    setFlags(QGraphicsTextItem::ItemIsSelectable | QGraphicsTextItem::ItemIsMovable);
    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable |
                            Qt::TextInteractionFlag::TextSelectableByKeyboard |
                            Qt::TextInteractionFlag::TextSelectableByMouse);
    setData(0, "text_item");
    setPlainText(str);
}

Text_item::~Text_item() = default;

QJsonObject *Text_item::get_text_item_info() {
    auto *info = new QJsonObject();
    info->insert("x", QJsonValue::fromVariant(x()));
    info->insert("y", QJsonValue::fromVariant(y()));
    info->insert("text", QJsonValue::fromVariant(toPlainText()));
    return info;
}

