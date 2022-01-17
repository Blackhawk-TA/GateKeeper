//
// Created by daniel on 17.01.22.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Nurse : public Character {
	private:
		const uint16_t TILE_ID = 132;
		const uint8_t BAR_HEIGHT = 1;

		void set_state(uint8_t new_state) override;

	public:
		explicit Nurse(map::MapSection map_section, Point position);
		~Nurse() override = default;
		void update(uint32_t time) override;
		void update_state(Point next_position) override;
		bool player_interact() override;
	};
}
