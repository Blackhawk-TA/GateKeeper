//
// Created by daniel on 24.11.21.
//

#include <iostream>
#include "enemy.hpp"
#include "../../../../engine/camera.hpp"
#include "../../player.hpp"

Enemy::Enemy(map::MapSections map_section, Point position, uint16_t tile_id, MovementDirection direction, bool turn)
	: Character(map_section, position, true, false) {
	Character::current_direction = direction;
	Enemy::tile_id = tile_id;
	Enemy::turn = turn;
	Enemy::in_action = false;
	last_turn = blit::now();
	animation_delay = ANIMATION_BASE_DELAY;
	movement_sprites = {
		{UP, {
			static_cast<uint16_t>(tile_id + 48),
			static_cast<uint16_t>(tile_id + 49),
			static_cast<uint16_t>(tile_id + 50),
			static_cast<uint16_t>(tile_id + 51)
		}},
		{DOWN, {
			tile_id,
			static_cast<uint16_t>(tile_id + 1),
			static_cast<uint16_t>(tile_id + 2),
			static_cast<uint16_t>(tile_id + 3)
		}},
		{LEFT, {
			static_cast<uint16_t>(tile_id + 16),
			static_cast<uint16_t>(tile_id + 17),
			static_cast<uint16_t>(tile_id + 18),
			static_cast<uint16_t>(tile_id + 19)
		}},
		{RIGHT, {
			static_cast<uint16_t>(tile_id + 32),
			static_cast<uint16_t>(tile_id + 33),
			static_cast<uint16_t>(tile_id + 34),
			static_cast<uint16_t>(tile_id + 35)
		}},
	};
}

void Enemy::update(uint32_t time) {
	//Handle random turning of enemy
	if (turn && time > animation_delay && last_turn < time - animation_delay) {
		uint8_t next_direction = blit::random() % DIRECTION_COUNT + 1;
		change_direction(static_cast<MovementDirection>(next_direction), false);

		last_turn = time;
		animation_delay = ANIMATION_BASE_DELAY + blit::random() % ANIMATION_VARIANCE;
	}

	//Trigger enemy to attack player
	if (!in_action && player_in_sightline()) {
		in_action = true;
		Player::set_cut_scene(true);
		walk_to_player();
	}
}

void Enemy::trigger_cut_scene() {

}

void Enemy::walk_to_next_tile(Character::MovementDirection direction) {

}

void Enemy::walk_to_player() {

}

bool Enemy::player_in_sightline() {
	Point player_position = camera::get_player_position();
	return (current_direction == UP && position.x == player_position.x && position.y > player_position.y)
		|| (current_direction == DOWN && position.x == player_position.x && position.y < player_position.y)
		|| (current_direction == LEFT && position.y == player_position.y && position.x > player_position.x)
		|| (current_direction == RIGHT && position.y == player_position.y && position.x < player_position.x);
}

void Enemy::set_state(uint8_t new_state) {}

void Enemy::update_state(Point next_position) {}

bool Enemy::player_interact() {
	return false;
}
