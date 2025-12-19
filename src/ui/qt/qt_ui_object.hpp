#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include "rect.hpp"

namespace biv {
class QtUIObject : public QGraphicsItem {
protected:
    Rect* game_object;  // Ссылка на игровой объект
    QColor color;       // Цвет объекта

public:
    QtUIObject(Rect* obj, const QColor& color);
    virtual ~QtUIObject() = default;

    // Обязательные методы QGraphicsItem
    QRectF boundingRect() const override;
    virtual void paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = nullptr) override;

    // Обновление позиции графического объекта
    virtual void updatePosition();

    // Обновление графики
    virtual void updateGraphics();

    // Получение игрового объекта
    Rect* get_game_object() const { return game_object; }

    // Установка цвета
    void setColor(const QColor& newColor) { color = newColor; }
    QColor getColor() const { return color; }

protected:
    // Переопределяем для поддержки изменения позиции
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
}
