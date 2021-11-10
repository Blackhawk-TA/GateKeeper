//
// Created by daniel on 27.02.21.
//

#include <assets.hpp>
#include "utils.hpp"
#include "saves/options.hpp"

using namespace blit;

/**
 * Checks if a rectangle of several sprites is currently shown at the screen
 * @param position The top left position of the sprite rectangle
 * @param size The size of the sprite rectangle
 * @param camera_position_world The current position of the camera in the world
 * @return True if at least one part of the sprite rectangle is currently shown at the screen
 */
bool sprite_rect_in_screen(Point &position, const Size &size, Point camera_position_world) {
	Point screen_tiles = get_screen_tiles();

	return camera_position_world.x < position.x + size.w &&
	       camera_position_world.y < position.y + size.h &&
	       screen_tiles.x + camera_position_world.x - position.x >= 0 &&
	       screen_tiles.y + camera_position_world.y - position.y >= 0;
}

Point screen_to_world(const Point &p) {
	return Point(p.x / TILE_SIZE, p.y / TILE_SIZE);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * TILE_SIZE, p.y * TILE_SIZE);
}

Point world_to_screen(const Vec2 &p) {
	return Point(std::ceil(p.x * TILE_SIZE), std::ceil(p.y * TILE_SIZE));
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
 * @return The amount of tiles that can be displayed at the screen stored as Point
 */
Point get_screen_tiles() {
	return Point(screen.bounds.w / TILE_SIZE, screen.bounds.h / TILE_SIZE);
}

/**
 * Loads all spritesheets that are persistently needed during the game's runtime
 */
void load_persistent_spritesheets() {
	screen.sprites = Surface::load_read_only(asset_spritesheet);

	player_sprites = Surface::load_read_only(asset_characters);
	player_attack_sprites = Surface::load_read_only(asset_player_attack);
}

void draw_fps(uint32_t &ms_start, uint32_t &ms_end) {
	//Abort if fps counter is hidden
	if (!options::show_fps) return;

	//Draw fps box
	screen.alpha = 255;
	screen.pen = Pen(255, 255, 255, 100);
	screen.rectangle(Rect(0, screen.bounds.h - 10, 20, 10));
	screen.pen = Pen(0, 0, 0, 200);

	//Calculate frames per second (fps)
	float time_difference_in_sec = static_cast<float>(ms_end - ms_start) / 1000;
	if (time_difference_in_sec == 0) {
		time_difference_in_sec = 1;
	}
	int fps = static_cast<int>(1 / time_difference_in_sec);

	//Cap max shown fps
	if (fps > 999) {
		fps = 999;
	}

	//Draw fps counter
	std::string fps_string = std::to_string(fps);
	screen.text(fps_string, minimal_font, Rect(1, screen.bounds.h - 10, 10, 10));

	//Draw frame time boxes
	int block_size = 4;
	for (int i = 0; i < static_cast<int>(ms_end - ms_start); i++) {
		screen.pen = Pen(i * 5, 255 - (i * 5), 0);
		screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
	}
}
