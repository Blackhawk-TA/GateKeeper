//
// Created by daniel on 02.09.21.
//

#pragma once
#include "utils.hpp"
#include "../engine/map.hpp"

using namespace blit;

/**
 * Connects the buildings with their interior by linking the coordinates on the specific tile maps.
 */
namespace entry_registry {
	struct Entry {
		Point exterior;
		Point interior;
		Point interior_offset;
		map::MapSections exterior_map;
		map::MapSections interior_map;
	};

	constexpr Entry connections[] = {
		Entry{Point(15, 12), Point(15, 13), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(29, 12), Point(37, 13), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(18, 19), Point(59, 13), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(27, 19), Point(82, 13), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(12, 44), Point(104, 13), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(52, 50), Point(19, 56), Point(1, 0), map::GRASSLAND, map::DUNGEON}
	};

	uint8_t get_id(Point &p, map::MapSections current_map);
}
