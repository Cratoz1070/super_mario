#pragma once

#include "mario.hpp"
#include "qt_ui_object.hpp"

namespace biv {
class QtMario : public Mario, public QtUIObject {
public:
    QtMario(const Coord& top_left, const int width, const int height);
    void updateGraphics() override;
};
}
