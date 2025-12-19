// qt_money.cpp
#include "qt_money.hpp"

using biv::QtMoney;

QtMoney::QtMoney(const Coord& top_left, const int width, const int height)
    : Money(top_left, width, height),
    QtUIObject(this, QColor(255, 215, 0)) {  // Gold
}

void QtMoney::updateGraphics() {
    updatePosition();
    update();
}
