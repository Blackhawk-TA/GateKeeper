//
// Created by daniel on 24.11.21.
//

#include "enemy.hpp"
#include "../../player.hpp"
#include "../../../../game.hpp"
#include "../../../../engine/effects/transition.hpp"

Enemy::Enemy(map::MapSections map_section, Point position, uint16_t tile_id, MovementDirection direction, bool turn)
	: Character(map_section, position, true, false) {
	Enemy::tile_id = tile_id;
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

	change_direction(direction, false);
}

void Enemy::update(uint32_t time) {
	Character::update(time);

	//Trigger enemy to attack player
	if (!in_action && !transition::in_progress() && player_in_sightline()) {
		in_action = true;
		is_moving = true;
		Player::start_cut_scene();
	}

	if (is_moving) {
		walk_to_player();
	}
}

void Enemy::trigger_cut_scene() {
	switch(current_direction) {
		case NO_DIRECTION:
			break;
		case UP:
			Player::change_direction(Player::MovementDirection::DOWN, false);
			break;
		case DOWN:
			Player::change_direction(Player::MovementDirection::UP, false);
			break;
		case LEFT:
			Player::change_direction(Player::MovementDirection::RIGHT, false);
			break;
		case RIGHT:
			Player::change_direction(Player::MovementDirection::LEFT, false);
			break;
	}

	//TODO might require temp save so returning after fight is not broken
	load_scene(Scene::COMBAT, 0, map_section);
}

void Enemy::set_state(uint8_t new_state) {}

void Enemy::update_state(Point next_position) {}

bool Enemy::player_interact() {
	return false;
}
