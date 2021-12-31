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
		void trigger_cut_scene() override;
		void close_textbox() override;
		void start_interaction();
		void start_fight();

		uint8_t save_id;
		std::string message;

	public:
		explicit Enemy(map::MapSection map_section, Point position, uint16_t tile_id, MovementDirection direction, uint8_t save_id, bool turn = false, std::string message = "");
		~Enemy() override = default;
		void update(uint32_t time) override;
		void update_state(Point next_position) override;
	};
}