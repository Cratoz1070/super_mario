#include "user_input.hpp"
#include <QKeyEvent>
#include <QApplication>
#include <QWidget>

namespace biv {
namespace os {

static bool keyA = false;
static bool keyD = false;
static bool keySpace = false;
static bool keyEscape = false;
static bool keyLeft = false;
static bool keyRight = false;

UserInput get_user_input() {
    if (keyA || keyLeft) {
        return UserInput::MAP_RIGHT;
    } else if (keyD || keyRight) {
        return UserInput::MAP_LEFT;
    } else if (keySpace) {
        return UserInput::MARIO_JUMP;
    } else if (keyEscape) {
        return UserInput::EXIT;
    } else {
        return UserInput::NO_INPUT;
    }
}

// Функции для обновления состояния клавиш (будут вызываться из Qt)
void set_key_state(int key, bool pressed) {
    switch (key) {
    case Qt::Key_A: keyA = pressed; break;
    case Qt::Key_D: keyD = pressed; break;
    case Qt::Key_Space: keySpace = pressed; break;
    case Qt::Key_Escape: keyEscape = pressed; break;
    case Qt::Key_Left: keyLeft = pressed; break;
    case Qt::Key_Right: keyRight = pressed; break;
    }
}

// Функция для сброса всех клавиш
void reset_keys() {
    keyA = false;
    keyD = false;
    keySpace = false;
    keyEscape = false;
    keyLeft = false;
    keyRight = false;
}
}
}
