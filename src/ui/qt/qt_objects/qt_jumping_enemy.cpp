// qt_jumping_enemy.cpp
#include "qt_jumping_enemy.hpp"

using biv::QtJumpingEnemy;

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, const int width, const int height)
    : JumpingEnemy(top_left, width, height),
    QtUIObject(this, QColor(255, 165, 0)) {  // Orange
}

void QtJumpingEnemy::updateGraphics() {
    updatePosition();
    update();
}
