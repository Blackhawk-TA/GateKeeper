//
// Created by daniel on 26.12.21.
//

#include "character.hpp"

#include <utility>
#include "../../../../engine/camera.hpp"
#include "../../ui/attack_menu.hpp"

namespace combat {
	Character::Character(CharacterData character_data, Point position, Point attack_position) {
		Character::position = position;
		Character::attack_position = attack_position;

		start_position = position;
		screen_position = world_to_screen(position);
		animation_sprites = character_data.movement_sprites;
		movement_sprites = character_data.movement_sprites;
		attack_sprites = character_data.attack_sprites;
		health = character_data.health;
		tile_id = animation_sprites.at(0);
		tile_index = 0;
		spritesheet_size = get_spritesheet_size(player_sprites->bounds);
		attack_spritesheet_size = get_spritesheet_size(player_attack_sprites->bounds);
		attack_state = IDLE;
	}

	void Character::draw() {
		if (attack_state == ATTACKING) {
			screen.blit(
				player_attack_sprites,
				Rect((tile_id % attack_spritesheet_size.w) * TILE_SIZE, (tile_id / attack_spritesheet_size.h) * TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE),
				screen_position - camera::get_screen_position() - Point(TILE_SIZE, TILE_SIZE));
		} else {
			screen.blit(
				player_sprites,
				Rect((tile_id & (spritesheet_size.w - 1)) * TILE_SIZE, (tile_id / spritesheet_size.h) * TILE_SIZE, SIZE.w * TILE_SIZE, SIZE.h * TILE_SIZE),
				screen_position - camera::get_screen_position()
			);
		}
	}

	void Character::update(uint32_t time) {
		switch (attack_state) {
			case IDLE:
				break;
			case WALKING_TO_ENEMY:
				walk_to_enemy();
				break;
			case ATTACKING:
				execute_attack();
				break;
			case WALKING_BACK:
				walk_back();
				break;
		}
	}

	void Character::animate_attack(std::function<void()> callback) {
		Character::damage_dealer = std::move(callback);
		attack_state = WALKING_TO_ENEMY;
	}

	void Character::walk_to_enemy() {
		if (direction == LEFT && position.x >= attack_position.x) {
			screen_position.x -= 1;
		} else if (direction == RIGHT && position.x <= attack_position.x) {
			screen_position.x += 1;
		} else {
			animation_sprites = attack_sprites;
			set_state(ATTACKING);
			if (damage_dealer != nullptr) {
				damage_dealer();
			}
		}

		position = screen_to_world(screen_position);
	}

	void Character::execute_attack() {
		if (tile_index == ANIMATION_SPRITE_COUNT - 1) {
			animation_sprites = movement_sprites;
			set_state(WALKING_BACK);
		}
	}

	void Character::walk_back() {
		if (direction == LEFT && position.x < start_position.x) {
			screen_position.x += 1;
		} else if (direction == RIGHT && position.x > start_position.x) {
			screen_position.x -= 1;
		} else {
			set_state(IDLE);
		}

		position = screen_to_world(screen_position);
	}

	void Character::set_state(Character::AttackState state) {
		attack_state = state;
		tile_index = 0;
		tile_id = animation_sprites[0];
	}

	void Character::animate(Timer &timer) {
		if (attack_state != IDLE) {
			tile_id = animation_sprites[++tile_index % ANIMATION_SPRITE_COUNT];
		}
	}

	uint8_t Character::get_health() const {
		return health;
	}

	void Character::take_damage(uint8_t amount) {
		if (health - amount > 0) {
			health -= amount;
		} else {
			health = 0;
			handle_death();
		}
	}

	void Character::handle_death() {
//		if (attack_menu::is_open()) {
//			attack_menu::close();
//		}
	}

	bool Character::use_stamina(uint8_t amount) {
		return true;
	}

	bool Character::is_attacking() const {
		return attack_state != IDLE;
	}
}
