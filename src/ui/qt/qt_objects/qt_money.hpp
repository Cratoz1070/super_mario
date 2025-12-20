#pragma once

#include "money.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtMoney : public Money, public QtUIObject {
public:
    QtMoney(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
