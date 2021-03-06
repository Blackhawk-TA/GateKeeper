//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../../utils/utils.hpp"
#include "../../../../game.hpp"
#include "../../../../utils/movement_direction.hpp"

namespace combat {
	class Character {
	public:
		enum CharacterType {
			Player = 1,
			Enemy = 2,
		};

		explicit Character(uint8_t save_id, const CharacterData& character_data, Point position, Point attack_position, MovementDirection direction);
		virtual ~Character() = default;
		virtual bool use_stamina(uint8_t amount);
		virtual CharacterType get_type() = 0;
		virtual void start_round() = 0;
		virtual void handle_round_end() = 0;
		virtual void draw();
		void finish_round();
		void update(uint32_t time);
		void animate(Timer &timer);
		uint8_t get_health() const;
		uint8_t get_max_health() const;
		void take_damage(uint8_t amount);
		void animate_attack(GEAR_TYPE type, std::function<void()> callback);
		bool is_attacking() const;
		uint8_t get_level() const;
		CharacterStats get_stats();

	protected:
		uint8_t health;
		uint8_t max_health;
		uint8_t level;
		uint8_t save_id;
		Point position;
		MovementDirection direction;
		CharacterStats stats;
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites{};

		virtual void handle_death() = 0;

	private:
		enum AttackState {
			IDLE = 0,
			WALKING_TO_ENEMY = 1,
			SWORD_ATTACK = 2,
			WALKING_BACK = 3,
			RANGE_ATTACK_INIT = 4,
			RANGE_ATTACK_TRAVEL = 5,
			RANGE_ATTACK_HIT = 6,
		};

		const uint8_t ATTACK_TILE_SIZE = 3;
		const uint16_t ROUND_END_DELAY = 750;
		const uint8_t WEAPON_INIT_ANIMATION_DELAY = 85;
		const uint8_t WEAPON_HIT_ANIMATION_DELAY = 125;
		const Size SIZE = Size(1, 1);
		bool round_finishing;
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites{};
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> attack_sprites{};
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> attack_sword_sprites{};
		uint32_t finish_time;
		uint32_t projectile_animation_time;
		uint16_t tile_id;
		uint8_t tile_index;
		uint8_t projectile_tile_id;
		uint8_t projectile_tile_index;
		uint8_t projectile_velocity;
		Point range_weapon_position; //The position of the range weapon in pixel
		Point screen_position;
		Point start_position;
		Point attack_position; //The position at which the attack animation is done
		Point target_position; //The position at where the enemy stands
		Point target_screen_position;
		Size spritesheet_size;
		Size attack_spritesheet_size;
		Size weapons_spritesheet_size;
		AttackState attack_state;
		GEAR_TYPE attack_type;
		std::function<void()> damage_dealer;

		void set_state(AttackState state);
		void walk_to_enemy();
		void execute_sword_attack();
		void walk_back();

		void set_weapon_state(AttackState state);
		void init_range_attack(uint32_t time);
		void execute_range_attack(uint32_t time);
		void hit_range_attack(uint32_t time);

		std::array<uint16_t, ANIMATION_SPRITE_COUNT> get_attack_sprites(GEAR_TYPE type);
	};
}