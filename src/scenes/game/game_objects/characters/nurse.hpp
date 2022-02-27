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

	public:
		explicit Nurse(map::MapSection map_section, Point position);
		~Nurse() override = default;
		bool player_interact() override;
	};
}
