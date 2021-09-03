//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include "player.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "building.hpp"

bool Player::is_moving = false;
Camera *Player::camera;
Timer *Player::animation_timer;
uint16_t Player::sprite_index = 0;
std::array<uint16_t, Player::ANIMATION_SPRITE_COUNT> Player::animation_sprites;

//Camera is scaled by the factor of 100 to prevent rounding issues
Player::Player(Camera *game_camera) {
	Player::start_position = get_screen_tiles() / 2;
	Player::position = start_position;
	Player::camera = game_camera;
	Player::characters = Surface::load(asset_characters);
	Player::sprite_sheet_size = get_sprite_sheet_size(Player::characters->bounds);

	//Set player animation tiles
	Player::current_direction = MovementDirection::DOWN;
	Player::animation_sprites = move_down_sprites;
	Player::sprite_index = animation_sprites[0];

	animation_timer = new Timer();
	animation_timer->init(animate, 175, -1);
}

void Player::animate(Timer &timer) {
	if (is_moving || camera->is_moving()) {
		sprite_index = animation_sprites[(sprite_index + 1) % ANIMATION_SPRITE_COUNT];
	} else {
		sprite_index = animation_sprites[0];
		animation_timer->stop(); //TODO when walking to the Door timer does not stop
	}
}

void Player::stop_movement() {
	is_moving = false;
}

void Player::move(MovementDirection direction) {
	Point movement = movement_map.at(direction);
	is_moving = true;

	//Do not trigger a movement while another one is in progress
	if (camera->is_moving()) {
		return;
	}

	//Start animation timer if not already running
	if (!animation_timer->is_running()) {
		animation_timer->start();
	}

	if (current_direction != direction) {
		switch (direction) {
			case UP:
				animation_sprites = move_up_sprites;
				break;
			case DOWN:
				animation_sprites = move_down_sprites;
				break;
			case LEFT:
				animation_sprites = move_left_sprites;
				break;
			case RIGHT:
				animation_sprites = move_right_sprites;
				break;
		}
		current_direction = direction;
		sprite_index = animation_sprites[0]; //Set sprite manually to avoid timer delay on player turn
	}

	Point next_position = camera->get_world_position() + position + movement;
	if (map::get_flag(next_position) != map::TileFlags::SOLID) {
		if (map::get_flag(next_position) == map::TileFlags::DOOR) {
			teleport(0, next_position); //TODO get building id dynamically
		}
		camera->move(movement);
	} else {
		is_moving = false;
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

/**
 * Teleports the player to the interior/exterior of the building and swaps the tile maps
 * @param building_id The id of the building
 * @param next_position The position where the player will walk within the next move
 */
void Player::teleport(uint8_t building_id, Point next_position) {
	Point destination;

	if (next_position == building::connections[building_id].exterior) {
		map::load_section(map::MapSections::INTERIOR);
		destination = building::connections[building_id].interior - get_screen_tiles() / 2;
	} else if (next_position == building::connections[building_id].interior) {
		map::load_section(map::MapSections::EXTERIOR);
		destination = building::connections[building_id].exterior - get_screen_tiles() / 2;
	}

	camera->set_position(destination);
}
