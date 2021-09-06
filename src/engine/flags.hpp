//
// Created by daniel on 07.09.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

namespace flags {
	enum TileFlags {
		SOLID = 1,
		DOOR = 2,
		COUNTER = 3
	};

	uint8_t get_flag(Point p);
	void set_flag(TileFlags flag, const std::vector<uint16_t> &tiles);
}
