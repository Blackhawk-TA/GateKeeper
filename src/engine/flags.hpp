//
// Created by daniel on 07.09.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

namespace flags {
	enum TileFlags {
		WALKABLE = 1,
		DOOR = 2,
		DEADLY = 3,
		COUNTER = 4
	};

	uint8_t get_flag(uint16_t tile_id);
	void set_flag(TileFlags flag, const std::vector<uint16_t> &tiles);
}
