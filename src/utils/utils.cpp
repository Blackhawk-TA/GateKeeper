//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / TILE_SIZE, p.y / TILE_SIZE);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * TILE_SIZE, p.y * TILE_SIZE);
}

Vec2 world_to_screen(const float &x, const float &y) {
	return Vec2(std::ceil(x * TILE_SIZE), std::ceil(y * TILE_SIZE));
}
