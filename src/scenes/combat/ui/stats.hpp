//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../utils/utils.hpp"

namespace combat::stats {
	const uint8_t TEXT_DISTANCE = 10;
	const uint8_t BAR_LENGTH = 100;
	const uint8_t BOX_Y_POS = 170;
	const uint8_t BOX_WIDTH = 110;

	void draw(uint8_t health, uint8_t stamina, uint8_t enemy_health);
}
