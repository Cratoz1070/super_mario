#include "flying.hpp"

using biv::Flying;

Flying::Flying(
	const Coord& top_left, 
	const int width, const int height, 
	const float vspeed, const float hspeed
) {
	this->top_left = top_left;
	this->width = width;
	this->height = height;
	this->vspeed = vspeed;
	this->hspeed = hspeed;
}

float Flying::get_vspeed() const noexcept {
	return vspeed;
}

void Flying::jump() noexcept {
	if (vspeed == 0) {
		vspeed = JUMP_SPEED;
	}
}

void Flying::move_horizontal_offset(const float offset) noexcept {
	top_left.x += offset;
}

void Flying::move_vertical_offset(const float offset) noexcept {
	top_left.y += offset;
}

// ----------------------------------------------------------------------------
// 									VIRTUAL
// ----------------------------------------------------------------------------
void Flying::move_horizontally() noexcept {
	top_left.x += hspeed;
}

void Flying::move_vertically() noexcept {
    if (!is_dead) {
        return;
    }
	if (vspeed < MAX_V_SPEED) {
		vspeed += V_ACCELERATION;
	}
	top_left.y += vspeed;
}
