//
// Created by daniel on 26.12.21.
//

#include "character.hpp"

#include <utility>
#include "../../../../engine/camera.hpp"
#include "assets.hpp"

namespace combat {
	Character::Character(uint8_t save_id, const CharacterData& character_data, Point position, Point attack_position, MovementDirection direction) {
		Character::save_id = save_id;
		Character::position = position;
		Character::attack_position = attack_position;
		Character::direction = direction;

		if (direction == LEFT) {
			target_position = attack_position - Point(1, 0);
		} else {
			target_position = attack_position + Point(1, 0);
		}

		start_position = position;
		target_screen_position = world_to_screen(target_position);
		screen_position = world_to_screen(position);
		animation_sprites = character_data.movement_sprites;
		movement_sprites = character_data.movement_sprites;
		attack_sword_sprites = character_data.attack_sprites;
		health = character_data.health;
		tile_id = animation_sprites.at(0);
		tile_index = 0;
		projectile_tile_id = 0;
		projectile_tile_index = 0;
		spritesheet_size = get_spritesheet_size(characters_spritesheet->bounds);
		attack_spritesheet_size = get_spritesheet_size(attack_spritesheet->bounds);
		weapons_spritesheet_size = get_spritesheet_size(weapons_spritesheet->bounds);
		attack_state = IDLE;
		attack_type = GEAR_NONE;
		round_finishing = false;
		finish_time = 0;
	}

	void Character::draw() {
		if (attack_state == SWORD_ATTACK) {
			screen.blit(
				attack_spritesheet,
				Rect((tile_id % attack_spritesheet_size.w) * TILE_SIZE, (tile_id / attack_spritesheet_size.h) * TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE),
				screen_position - camera::get_screen_position() - Point(TILE_SIZE, TILE_SIZE));
		} else {
			screen.blit(
				characters_spritesheet,
				Rect((tile_id & (spritesheet_size.w - 1)) * TILE_SIZE, (tile_id / spritesheet_size.h) * TILE_SIZE, SIZE.w * TILE_SIZE, SIZE.h * TILE_SIZE),
				screen_position - camera::get_screen_position()
			);

			if (attack_state == RANGE_ATTACK_INIT || attack_state == RANGE_ATTACK_TRAVEL || attack_state == RANGE_ATTACK_HIT) {
				screen.blit(
					weapons_spritesheet,
					Rect((projectile_tile_id % weapons_spritesheet_size.w) * TILE_SIZE, (projectile_tile_id / weapons_spritesheet_size.h) * TILE_SIZE, SIZE.w * TILE_SIZE, SIZE.h * TILE_SIZE),
					range_weapon_position - camera::get_screen_position()
				);

			}
		}
	}

	void Character::update(uint32_t time) {
		if (round_finishing && finish_time + ROUND_END_DELAY <= time) {
			round_finishing = false;
			handle_round_end();
		}

		switch (attack_state) {
			case IDLE:
				break;
			case WALKING_TO_ENEMY:
				walk_to_enemy();
				break;
			case SWORD_ATTACK:
				execute_sword_attack();
				break;
			case WALKING_BACK:
				walk_back();
				break;
			case RANGE_ATTACK_INIT:
				init_range_attack(time);
				break;
			case RANGE_ATTACK_TRAVEL:
				execute_range_attack(time);
				break;
			case RANGE_ATTACK_HIT:
				hit_range_attack(time);
				break;
		}
	}

	void Character::animate_attack(GEAR_TYPE type, std::function<void()> callback) {
		Character::damage_dealer = std::move(callback);

		attack_type = type;
		attack_sprites = get_attack_sprites(type);
		if (attack_type != GEAR_SWORD) {
			projectile_animation_time = blit::now();
			range_weapon_position = screen_position;
			if (attack_type == GEAR_ARROW || attack_type == GEAR_DAGGER || attack_type == GEAR_SPEAR) {
				projectile_velocity = 2;
			} else {
				projectile_velocity = 1;
			}
			set_weapon_state(RANGE_ATTACK_INIT);
		} else {
			set_state(WALKING_TO_ENEMY);
		}
	}

	void Character::walk_to_enemy() {
		if (direction == LEFT && position.x >= attack_position.x) {
			screen_position.x -= 1;
		} else if (direction == RIGHT && position.x < attack_position.x) {
			screen_position.x += 1;
		} else {
			animation_sprites = attack_sprites;
			set_state(SWORD_ATTACK);
			if (damage_dealer != nullptr) {
				damage_dealer();
			}
		}

		position = screen_to_world(screen_position);
	}

	void Character::execute_sword_attack() {
		if (tile_index == ANIMATION_SPRITE_COUNT - 1) {
			animation_sprites = movement_sprites;
			set_state(WALKING_BACK);
		}
	}

	void Character::walk_back() {
		if (direction == LEFT && position.x < start_position.x) {
			screen_position.x += 1;
		} else if (direction == RIGHT && position.x >= start_position.x) {
			screen_position.x -= 1;
		} else {
			set_state(IDLE);
			finish_round();
		}

		position = screen_to_world(screen_position);
	}

	void Character::init_range_attack(uint32_t time) {
		if (projectile_animation_time + WEAPON_INIT_ANIMATION_DELAY > time) {
			set_weapon_state(RANGE_ATTACK_INIT);
			if (direction == LEFT) {
				range_weapon_position.x -= projectile_velocity;
			} else if (direction == RIGHT) {
				range_weapon_position.x += projectile_velocity;
			}
		} else {
			set_weapon_state(RANGE_ATTACK_TRAVEL);
		}
	}

	void Character::execute_range_attack(uint32_t time) {
		if ((direction == LEFT && range_weapon_position.x <= target_screen_position.x)
		|| (direction == RIGHT && range_weapon_position.x >= target_screen_position.x)) {
			projectile_animation_time = time;
			set_weapon_state(RANGE_ATTACK_HIT);
		} else if (direction == LEFT) {
			range_weapon_position.x -= projectile_velocity;
		} else if (direction == RIGHT) {
			range_weapon_position.x += projectile_velocity;
		}
	}

	void Character::hit_range_attack(uint32_t time) {
		if (projectile_animation_time + WEAPON_HIT_ANIMATION_DELAY < time) {
			damage_dealer();
			set_weapon_state(IDLE);
			finish_round();
		}
	}

	void Character::set_state(Character::AttackState state) {
		attack_state = state;
		tile_index = 0;
		tile_id = animation_sprites[0];
	}

	void Character::set_weapon_state(Character::AttackState state) {
		bool has_init_sprite = attack_type == GEAR_FIRE || attack_type == GEAR_ICE || attack_type == GEAR_SHOCK || attack_type == GEAR_MAGIC;
		attack_state = state;

		switch (state) {
			case RANGE_ATTACK_INIT:
				projectile_tile_index = 0;
				break;
			case RANGE_ATTACK_TRAVEL:
				projectile_tile_index = has_init_sprite ? 1 : 0;
				break;
			case RANGE_ATTACK_HIT:
				projectile_tile_index = has_init_sprite ? 2 : 1;
				break;
			default:
				projectile_tile_index = 0;
				break;
		}

		projectile_tile_id = attack_sprites[projectile_tile_index];
	}

	void Character::animate(Timer &timer) {
		if (attack_state != IDLE && attack_type == GEAR_SWORD) {
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

	bool Character::use_stamina(uint8_t amount) {
		return true;
	}

	bool Character::is_attacking() const {
		return attack_state != IDLE;
	}

	void Character::finish_round() {
		round_finishing = true;
		attack_type = GEAR_NONE;
		finish_time = blit::now();
	}

	std::array<uint16_t, ANIMATION_SPRITE_COUNT> Character::get_attack_sprites(GEAR_TYPE type) {
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> sprites = {};

		switch (type) {
			case GEAR_SWORD:
				sprites = attack_sword_sprites;
				break;
			case GEAR_DAGGER:
				direction == RIGHT ? sprites = {2, 8} : sprites = {3, 9};
				break;
			case GEAR_ARROW:
				direction == RIGHT ? sprites = {1, 8} : sprites = {4, 9};
				break;
			case GEAR_SPEAR:
				direction == RIGHT ? sprites = {0, 8} : sprites = {5, 9};
				break;
			case GEAR_FIRE:
				direction == RIGHT ? sprites = {12, 13, 14} : sprites = {17, 16, 15};
				break;
			case GEAR_ICE:
				direction == RIGHT ? sprites = {18, 19, 20} : sprites = {23, 22, 21};
				break;
			case GEAR_SHOCK:
				direction == RIGHT ? sprites = {24, 25, 26} : sprites = {29, 28, 27};
				break;
			case GEAR_MAGIC:
				direction == RIGHT ? sprites = {30, 31, 32} : sprites = {35, 34, 33};
				break;
			case GEAR_NONE:
				break;
		}

		return sprites;
	}

	CharacterStats Character::get_stats() {
		return stats;
	}
}
