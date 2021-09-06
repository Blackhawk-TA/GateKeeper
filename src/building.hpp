//
// Created by daniel on 02.09.21.
//

#pragma once
#include "utils/utils.hpp"
#include "map.hpp"

using namespace blit;

/**
 * Connects the buildings with their interior by linking the coordinates on the specific tile maps.
 */
namespace building {
	struct Door {
		Point exterior;
		Point interior;
	};

	constexpr Door connections[] = {
			Door{Point(19, 15), Point(15, 13)},
			Door{Point(26, 15), Point(37, 13)}
	};

	uint8_t get_id(Point &p, map::MapSections map_section);
}
