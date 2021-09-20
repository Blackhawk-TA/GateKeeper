//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

/**
 * Checks if a point is within a rectangle defined by a min and max point
 * @param p The point which shall be checked
 * @param min_x The position at which the rectangle begins on the x-axis
 * @param min_y The position at which the rectangle begins on the y-axis
 * @param max_x The position at which the rectangle ends on the x-axis
 * @param max_y The position at which the rectangle ends on the y-axis
 * @return True if the point p is within the rectangle, else false
 */
bool point_in_rect(Point &p, uint8_t min_x, uint8_t min_y, uint8_t max_x, uint8_t max_y) {
	return (((p.x == min_x && p.y >= min_y) || p.x > min_x) &&
	        ((p.x == max_x && p.y <= max_y) || p.x < max_x));
}

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

//Get amount of tiles on a spritesheet's x and y-axis
Point get_sprite_sheet_size(Size bounds) {
	return Point(bounds.w / TILE_SIZE, bounds.h / TILE_SIZE);
}

//Get amount of tiles that can be displayed on the screen's x and y-axis
Point get_screen_tiles() {
	return Point(screen.bounds.w / TILE_SIZE, screen.bounds.h / TILE_SIZE);
}
