//
// Created by daniel on 21.08.21.
//

#include "player.hpp"
#include "utils/camera.hpp"

//Camera is scaled by the factor of 100 to prevent rounding issues
Player::Player(Camera *camera) {
	Player::start_position = get_screen_tiles() / 2;
	Player::position = start_position;
	Player::sprite_sheet_size = get_sprite_sheet_size();
	Player::camera = camera;
}

void Player::move_up() {
	move(Point(0, -1));
}

void Player::move_down() {
	move(Point(0, 1));
}

void Player::move_left() {
	move(Point(-1, 0));
}

void Player::move_right() {
	move(Point(1, 0));
}

void Player::move(Point movement) {
//	Point next_position = camera->get_world_position() + movement;
	if (!camera->is_moving() /*&& map::get_flag(next_position) == map::TileFlags::SOLID*/) {
		camera->move(movement);
	}
}

void Player::draw() {
	screen.blit_sprite(
		Rect((tile_id % sprite_sheet_size.x) * TILE_SIZE, (tile_id / sprite_sheet_size.y ) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
		world_to_screen(position),
		SpriteTransform::NONE
	);
}
