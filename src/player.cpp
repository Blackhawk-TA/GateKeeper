//
// Created by daniel on 21.08.21.
//

#include "player.hpp"
#include "utils/map.hpp"

constexpr uint8_t camera_scale = 100;
constexpr float camera_scale_float = 100.0f;

//Camera is scaled by the factor of 100 to prevent rounding issues
Player::Player() {
	Player::start_position = Point(10, 7);
	Player::position = start_position;
	Player::camera = Point(0, 0);
	Player::camera_offset = Point(0, 0);
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

void Player::move(Point player_movement) {
//	Point next_position = camera + player_movement;
	if (!is_moving /*&& map::get_flag(next_position) == map::TileFlags::SOLID*/) {
		camera_offset = player_movement * camera_scale;
		is_moving = true;
	}
}

void Player::draw() {
	screen.blit_sprite(
		Rect((tile_id % SPRITE_SHEET_SIZE.x) * TILE_SIZE, (tile_id / SPRITE_SHEET_SIZE.y ) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
		world_to_screen(position),
		SpriteTransform::NONE
	);
}


Point Player::update_camera() {
	if (!is_moving) {
		return world_to_screen((float)camera.x / camera_scale_float, (float)camera.y / camera_scale_float);
	}

	if (camera_offset.x != 0) {
		if (camera.x < camera.x + camera_offset.x) {
			camera.x += velocity;
			camera_offset.x -= velocity;
		} else if (camera.x > camera.x + camera_offset.x) {
			camera.x -= velocity;
			camera_offset.x += velocity;
		}
	} else if (camera_offset.y != 0) {
		if (camera.y < camera.y + camera_offset.y) {
			camera.y += velocity;
			camera_offset.y -= velocity;
		} else if (camera.y > camera.y + camera_offset.y) {
			camera.y -= velocity;
			camera_offset.y += velocity;
		}
	} else {
		is_moving = false;
	}

	return world_to_screen((float)camera.x / camera_scale_float, (float)camera.y / camera_scale_float);
}
