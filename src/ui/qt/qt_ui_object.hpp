#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include "rect.hpp"

namespace biv {
class QtUIObject : public QGraphicsItem {
protected:
    Rect* game_object;  
    QColor color;       

public:
    QtUIObject(Rect* obj, const QColor& color);
    virtual ~QtUIObject() = default;

    QRectF boundingRect() const override;
    virtual void paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = nullptr) override;

    virtual void updatePosition();

    virtual void updateGraphics();

    Rect* get_game_object() const { return game_object; }

    void setColor(const QColor& newColor) { color = newColor; }
    QColor getColor() const { return color; }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
}
