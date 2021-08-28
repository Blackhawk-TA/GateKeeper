//
// Created by daniel on 28.08.21.
//

#pragma once
#include "map_handler.hpp"
#include "../utils/utils.hpp"

using namespace blit;

class MapSegment {
public:
	explicit MapSegment();
	void calculate_layer_data(); //Pre-calculate layer_data

private:
	//TODO make sure flags, layer count and layer_data is individual for each map segment
	std::array<std::vector<uint16_t>, map::TileFlags::COUNTER> flags;
	std::array<std::array<uint16_t, LEVEL_SIZE>, LAYER_COUNT> layer_data;
};
