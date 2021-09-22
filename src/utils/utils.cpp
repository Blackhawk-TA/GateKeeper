//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

/**
 * Checks if a rectangle of several sprites is currently shown at the screen
 * @param position The top left position of the sprite rectangle
 * @param size The size of the sprite rectangle
 * @param camera_position_world The current position of the camera in the world
 * @return True if at least one part of the sprite rectangle is currently shown at the screen
 */
bool sprite_rect_in_screen(Point &position, const Size &size, Point &camera_position_world) {
	Point screen_tiles = get_screen_tiles();

	return camera_position_world.x < position.x + size.w &&
	       camera_position_world.y < position.y + size.h &&
	       screen_tiles.x + camera_position_world.x - position.x > 0 &&
	       screen_tiles.y + camera_position_world.y - position.y > 0;
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

/**
 * Get amount of tiles on a spritesheet's x and y-axis
 * @param bounds The bounds of the spritesheet
 * @return The amount of tiles a spritesheet can fit stored as Size
 */
Size get_spritesheet_size(Size bounds) {
	return Size(bounds.w / TILE_SIZE, bounds.h / TILE_SIZE);
}

/**
 * Get amount of tiles that can be displayed on the screen's x and y-axis
 * @return The amoutn of tiles that can be displayed at the screen stored as Point
 */
Point get_screen_tiles() {
	return Point(screen.bounds.w / TILE_SIZE, screen.bounds.h / TILE_SIZE);
}
