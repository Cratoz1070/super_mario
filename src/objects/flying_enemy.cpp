#include "flying_enemy.hpp"

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.2;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::kill_enemy() noexcept {
    if (is_active()) {
        kill();
        vspeed = 0; 
    }
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	if (!is_active()) return;
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (!is_active()) return;

	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill_enemy();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	if (!is_active()) return;
	// Проверка: не свалился ли враг с корабля. 
	// Т.е., если он на краю, то он должен разверуться 
	// и побежать в обратную сторону.
	top_left.x += hspeed;
	if (!has_collision(obj)) {
		process_horizontal_static_collision(obj);
	} else {
		top_left.x -= hspeed;
	}
	
	// Особенность модели вертикального передвижения в игре.
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}

void FlyingEnemy::move_vertically() noexcept {
    if (is_active()) {
		
    } else {
        vspeed += V_ACCELERATION;
        if (vspeed > MAX_V_SPEED) {
            vspeed = MAX_V_SPEED;
        }
        top_left.y += vspeed; 
    }
}
