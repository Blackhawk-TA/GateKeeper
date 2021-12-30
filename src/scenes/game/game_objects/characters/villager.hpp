//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Villager : public Character {
	private:
		std::string message;

		void set_state(uint8_t new_state) override;

	public:
		explicit Villager(map::MapSection map_section, Point position, uint16_t tile_id, MovementDirection direction, std::string message);
		~Villager() override = default;
		void update_state(Point next_position) override;
		bool player_interact() override;
		void close_textbox() override;
	};
}
