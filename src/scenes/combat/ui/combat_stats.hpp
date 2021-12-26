//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../utils/utils.hpp"

namespace combat_stats {
	const uint8_t TEXT_DISTANCE = 10;
	const uint8_t BAR_LENGTH = 107;
	const std::string STATUS_BARS[3] = {"Health", "Stamina", "Enemy"};

	void draw(uint8_t health, uint8_t stamina, uint8_t enemy_health);
}
