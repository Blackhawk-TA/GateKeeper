//
// Created by daniel on 24.11.21.
//

#include "enemy.hpp"
#include "../../../../engine/camera.hpp"
#include "../../player.hpp"
#include "../../../../game.hpp"

Enemy::Enemy(map::MapSections map_section, Point position, uint16_t tile_id, MovementDirection direction, bool turn)
	: Character(map_section, position, true, false) {
	Enemy::tile_id = tile_id;
	Enemy::turn = turn;
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

	change_direction(direction, false);
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
		is_moving = true;
		Player::set_cut_scene(true);
	}

	if (is_moving) {
		walk_to_player();
	}
}

void Enemy::walk_to_player() {
	Point player_position = camera::get_player_position();

	if (current_direction == UP && position.y - 1 > player_position.y) {
		screen_position.y -= 1;
	} else if (current_direction == DOWN && position.y + 1 < player_position.y) {
		screen_position.y += 1;
	} else if (current_direction == LEFT && position.x - 1 > player_position.x) {
		screen_position.x -= 1;
	} else if (current_direction == RIGHT && position.x + 1 < player_position.x) {
		screen_position.x += 1;
	} else {
		//Enemy is standing in front of player and starts combat
		is_moving = false;
		tile_id = animation_sprites[0];
		load_scene(Scene::MENU); //TODO load combat scene
	}

	position = screen_to_world(screen_position);
}

bool Enemy::player_in_sightline() {
	Point player_position = camera::get_player_position();
	return (current_direction == UP && position.x == player_position.x && position.y > player_position.y)
		|| (current_direction == DOWN && position.x == player_position.x && position.y < player_position.y)
		|| (current_direction == LEFT && position.y == player_position.y && position.x > player_position.x)
		|| (current_direction == RIGHT && position.y == player_position.y && position.x < player_position.x);
}

void Enemy::animate() {
	if (is_moving) {
		tile_id = animation_sprites[++tile_index % ANIMATION_SPRITE_COUNT];
	}
}

void Enemy::set_state(uint8_t new_state) {}

void Enemy::update_state(Point next_position) {}

bool Enemy::player_interact() {
	return false;
}
