#include "qt_box.hpp"

using biv::QtBox;

QtBox::QtBox(const Coord& top_left, const int width, const int height)
    : Box(top_left, width, height),
    QtUIObject(this, QColor(139, 69, 19)) {  
}

void QtBox::updateGraphics() {
    updatePosition();
    update();
}
