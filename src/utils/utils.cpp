//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / TILE_SIZE, p.y / TILE_SIZE);
}

Point screen_to_world(const Point &p) {
	return Point(p.x / TILE_SIZE, p.y / TILE_SIZE);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * TILE_SIZE, p.y * TILE_SIZE);
}

Point world_to_screen(const float &x, const float &y) {
	return Point(std::ceil(x * TILE_SIZE), std::ceil(y * TILE_SIZE));
}
