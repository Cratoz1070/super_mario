// qt_enemy.hpp
#pragma once

#include "enemy.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtEnemy : public Enemy, public QtUIObject {
public:
    QtEnemy(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
