#include "qt_full_box.hpp"
#include <QPainter>

using biv::QtFullBox;

QtFullBox::QtFullBox(
    const Coord& top_left,
    const int width, const int height,
    UIFactory* ui_factory
    ) : FullBox(top_left, width, height, ui_factory),
    QtUIObject(this, QColor(255, 215, 0)) {  
}

void QtFullBox::updateGraphics() {
    updatePosition();
    update();
}

void QtFullBox::paint(QPainter* painter,
                      const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
    if (is_active_) {
        painter->setBrush(QColor(255, 215, 0));  
    } else {
        painter->setBrush(QColor(139, 69, 19));  
    }
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());

    if (is_active_) {
        painter->setPen(Qt::black);
        painter->setFont(QFont("Arial", 10));
        painter->drawText(boundingRect(), Qt::AlignCenter, "?");
    }
}
