//
// Created by daniel on 07.09.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

namespace flags {
	enum TileFlags {
		NO_FLAG = 0,
		WALKABLE = 1,
		ELEVATE_1PX = 2,
		ELEVATE_2PX = 3,
		ELEVATE_3PX = 4,
		ENTRY = 5,
		DEADLY = 6,
		TREE = 7,
		COUNTER = 8
	};

	uint8_t get_flag(uint16_t tile_id);
	void set_flags(TileFlags flag, const std::vector<uint16_t> &tiles);
}
