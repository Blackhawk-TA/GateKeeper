//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Enemy : public Character {
	private:
		const uint8_t MAX_HEALTH = 100;
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
		uint8_t level;
		std::string message;
		CombatCharacterType character_type;
		bool can_respawn;

	public:
		explicit Enemy(map::MapSection map_section, Point position, uint8_t level, CombatCharacterType character_type, MovementDirection direction, uint8_t save_id, bool turn = false, std::string message = "", bool can_respawn = true);
		~Enemy() override = default;
		void update(uint32_t time) override;
		GameObject::ObjectType get_type() override;
		bool can_be_respawned() const;

		/**
		 * Set active property only when can_respawn is set to true, otherwise it can only be set to false
		 * @param active The active value
		 */
		void set_active(bool active) override;
	};
}
