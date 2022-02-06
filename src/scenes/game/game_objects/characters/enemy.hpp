//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Enemy : public Character {
	private:
		void set_state(uint8_t new_state) override;
		bool player_interact() override;
		void trigger_cutscene() override;
		void close_textbox() override;
		void start_interaction();
		void start_fight();
		uint16_t get_init_tile_id();

		/**
		 * Get the stats for each enemy type including their available attacks and damage multiplier
		 * @return  The attack stats of the enemy depending on the character_type
		 */
		CharacterStats get_stats();

		uint8_t save_id;
		std::string message;
		CombatCharacterType character_type;

	public:
		explicit Enemy(map::MapSection map_section, Point position, CombatCharacterType character_type, MovementDirection direction, uint8_t save_id, bool turn = false, std::string message = "");
		~Enemy() override = default;
		void update(uint32_t time) override;
		void update_state(Point next_position) override;
	};
}