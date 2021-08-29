//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include "player.hpp"
#include "camera.hpp"
#include "map.hpp"

uint16_t Player::sprite_index = 0;
std::array<uint16_t, Player::ANIMATION_SPRITE_COUNT> Player::animation_sprites;

//Camera is scaled by the factor of 100 to prevent rounding issues
Player::Player(Camera *camera) {
	Player::start_position = get_screen_tiles() / 2;
	Player::position = start_position;
	Player::camera = camera;
	Player::characters = Surface::load(asset_characters);
	Player::sprite_sheet_size = get_sprite_sheet_size(Player::characters->bounds);

	//Set player animation tiles
	Player::move_down_sprites = {0, 1, 2, 3};
	Player::move_left_sprites = {16, 17, 18, 19};
	Player::move_right_sprites = {32, 33, 34, 35};
	Player::move_up_sprites = {48, 49, 50, 51};
	Player::animation_sprites = move_down_sprites;
	Player::sprite_index = animation_sprites[0];

	animation_timer.init(animate, 175, -1);
	animation_timer.start();
}

void Player::animate(Timer &timer) {
	sprite_index = animation_sprites[(sprite_index + 1) % 4];
}

void Player::move_up() {
	animation_sprites = move_up_sprites;
	move(Point(0, -1));
}

void Player::move_down() {
	animation_sprites = move_down_sprites;
	move(Point(0, 1));
}

void Player::move_left() {
	animation_sprites = move_left_sprites;
	move(Point(-1, 0));
}

void Player::move_right() {
	animation_sprites = move_right_sprites;
	move(Point(1, 0));
}

void Player::move(Point movement) {
	sprite_index = animation_sprites[(sprite_index) % 4]; //Set sprite manually to avoid timer delay on player turn

	Point next_position = camera->get_world_position() + position + movement;
	if (!camera->is_moving() && map::get_flag(next_position) != map::TileFlags::SOLID) {
		camera->move(movement);
	}
}

void Player::draw() {
	screen.blit(
		characters,
		Rect((sprite_index % sprite_sheet_size.x) * TILE_SIZE, (sprite_index / sprite_sheet_size.y ) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
		world_to_screen(position),
		SpriteTransform::NONE
	);
}
