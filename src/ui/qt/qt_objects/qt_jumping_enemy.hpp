// qt_jumping_enemy.hpp
#pragma once

#include "jumping_enemy.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtJumpingEnemy : public JumpingEnemy, public QtUIObject {
public:
    QtJumpingEnemy(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
