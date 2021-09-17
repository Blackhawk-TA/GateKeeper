//
// Created by daniel on 02.09.21.
//

#pragma once
#include "utils/utils.hpp"
#include "engine/map.hpp"

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
			Door{Point(15, 12), Point(15, 13)},
			Door{Point(29, 12), Point(37, 13)},
			Door{Point(18, 19), Point(59, 13)},
			Door{Point(27, 19), Point(82, 13)}
	};

	uint8_t get_id(Point &p, map::MapSections map_section);
}
