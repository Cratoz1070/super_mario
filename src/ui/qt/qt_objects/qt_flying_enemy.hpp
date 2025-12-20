#pragma once

#include "flying_enemy.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtFlyingEnemy : public FlyingEnemy, public QtUIObject {
public:
    QtFlyingEnemy(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
