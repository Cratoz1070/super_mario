// qt_box.hpp
#pragma once

#include "box.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtBox : public Box, public QtUIObject {
public:
    QtBox(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
