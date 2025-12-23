#pragma once

#include "user_input.hpp"
#include <QKeyEvent>

namespace biv {
namespace os {

UserInput get_user_input();
void set_key_state(int key, bool pressed);
void reset_keys();

}
}
