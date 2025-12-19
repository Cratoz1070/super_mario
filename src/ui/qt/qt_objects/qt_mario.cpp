// qt_mario.cpp
#include "qt_mario.hpp"

using biv::QtMario;

QtMario::QtMario(const Coord& top_left, const int width, const int height)
    : Mario(top_left, width, height),
    QtUIObject(this, Qt::red) {
}

void QtMario::updateGraphics() {
    updatePosition();
    update();
}
