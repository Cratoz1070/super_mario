#pragma once

#include "ship.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtShip : public Ship, public QtUIObject {
public:
    QtShip(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
