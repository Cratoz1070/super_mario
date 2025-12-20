#pragma once

#include "full_box.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtFullBox : public FullBox, public QtUIObject {
public:
    QtFullBox(
        const Coord& top_left,
        const int width, const int height,
        UIFactory* ui_factory
        );
    void updateGraphics() override;

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
};
}
