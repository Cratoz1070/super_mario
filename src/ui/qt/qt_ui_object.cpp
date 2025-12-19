// qt_ui_object.cpp
#include "qt_ui_object.hpp"

using biv::QtUIObject;

QtUIObject::QtUIObject(Rect* obj, const QColor& color)
    : game_object(obj), color(color) {
    updatePosition();
}

QRectF QtUIObject::boundingRect() const {
    if (!game_object) return QRectF();

    // Вычисляем ширину и высоту через координаты
    int width = game_object->get_right() - game_object->get_left();
    int height = game_object->get_bottom() - game_object->get_top();

    return QRectF(0, 0, width, height);
}

void QtUIObject::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget) {
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

void QtUIObject::updatePosition() {
    if (!game_object) return;
    setPos(game_object->get_left(), game_object->get_top());
}

void QtUIObject::updateGraphics() {
    updatePosition();
    update();  // Перерисовка
}

QVariant QtUIObject::itemChange(GraphicsItemChange change, const QVariant &value) {
    // Обработка изменений элемента (например, изменение позиции)
    return QGraphicsItem::itemChange(change, value);
}
