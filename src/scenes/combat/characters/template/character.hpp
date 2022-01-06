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
		static const uint8_t MAX_HEALTH = 100;

		explicit Character(uint8_t save_id, CharacterData character_data, Point position, Point attack_position);
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
		void take_damage(uint8_t amount);
		void animate_attack(std::function<void()> callback);
		bool is_attacking() const;

	protected:
		MovementDirection direction;
		uint8_t health;
		uint8_t save_id;
		Point position;
		virtual void handle_death() = 0;

	private:
		enum AttackState {
			IDLE = 0,
			WALKING_TO_ENEMY = 1,
			ATTACKING = 2,
			WALKING_BACK = 3
		};

		const uint8_t ATTACK_TILE_SIZE = 3;
		const uint16_t ROUND_END_DELAY = 750;
		const Size SIZE = Size(1, 1);
		bool round_finishing;
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites{};
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites{};
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> attack_sprites{};
		uint32_t finish_time;
		uint16_t tile_id;
		uint8_t tile_index;
		Point screen_position;
		Point start_position;
		Point attack_position; //The position at which the attack animation is done
		Size spritesheet_size;
		Size attack_spritesheet_size;
		Size weapons_spritesheet_size;
		AttackState attack_state;
		std::function<void()> damage_dealer;

		void set_state(AttackState state);
		void walk_to_enemy();
		void execute_attack();
		void walk_back();
	};
}