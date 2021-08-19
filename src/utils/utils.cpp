//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / TILE_SIZE, p.y / TILE_SIZE);
}

Point world_to_screen(const Point &p) {
	return {p.x * TILE_SIZE, p.y * TILE_SIZE};
}

Point world_to_screen(const int &x, const int &y) {
	return {x * TILE_SIZE, y * TILE_SIZE};
}
