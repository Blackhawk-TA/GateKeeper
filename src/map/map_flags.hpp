//
// Created by daniel on 28.08.21.
//

#pragma once
#include "map_handler.hpp"
#include "../utils/utils.hpp"

using namespace blit;

class MapFlags {
public:
	enum TileFlags {
		SOLID = 1,
		COUNTER = 2
	};

	explicit MapFlags(uint8_t layer_count);
	void set_flags(TileFlags flag, const std::vector<uint16_t> &tiles);
	uint8_t get_flag(Point p);

private:
	uint8_t layer_count;
	std::array<std::vector<uint16_t>, TileFlags::COUNTER> flags;
};
