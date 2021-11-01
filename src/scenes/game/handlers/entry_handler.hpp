//
// Created by daniel on 02.09.21.
//

#pragma once
#include "../../../utils/utils.hpp"
#include "../../../engine/map.hpp"

using namespace blit;

/**
 * Connects the entries with their interior by linking the coordinates on the specific tile maps.
 */
namespace entry_handler {
	struct Entry {
		Point exterior;
		Point interior;
		Point interior_offset;
		map::MapSections exterior_map;
		map::MapSections interior_map;
	};

	constexpr Entry connections[] = {
		Entry{Point(15, 12), Point(6, 9), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(29, 12), Point(28, 9), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(18, 19), Point(50, 9), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(27, 19), Point(6, 25), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(12, 44), Point(28, 25), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(52, 50), Point(19, 56), Point(1, 0), map::GRASSLAND, map::DUNGEON}
	};

	uint8_t get_id(Point &p, map::MapSections current_map);
	void teleport(uint8_t entry_id, Point next_position);
	bool enter(Point &next_position);
}
