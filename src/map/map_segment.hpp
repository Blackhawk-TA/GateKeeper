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

private:
	std::array<std::vector<uint16_t>, map::TileFlags::COUNTER> flags;
};
