// qt_flying_enemy.cpp
#include "qt_flying_enemy.hpp"

using biv::QtFlyingEnemy;

QtFlyingEnemy::QtFlyingEnemy(const Coord& top_left, const int width, const int height)
    : FlyingEnemy(top_left, width, height),
    QtUIObject(this, QColor(255, 0, 0, 180)) {  // Semi-transparent red
}

void QtFlyingEnemy::updateGraphics() {
    updatePosition();
    update();
}
