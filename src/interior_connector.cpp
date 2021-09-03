//
// Created by daniel on 02.09.21.
//

#include "interior_connector.hpp"
#include "utils/utils.hpp"
#include "map.hpp"

using namespace blit;

namespace interior_connector {
	struct Door {
		Point exterior;
		Point interior;
	};

	constexpr Door connections[] = {
			Door{Point(19, 15), Point(15, 13)}
	};

	Point teleport(uint8_t building_id, Point position) {
		if (position == connections[building_id].exterior) {
			map::load_section(map::MapSections::INTERIOR);
			return connections[building_id].interior - get_screen_tiles() / 2;
		} else if (position == connections[building_id].interior) {
			map::load_section(map::MapSections::EXTERIOR);
			return connections[building_id].exterior - get_screen_tiles() / 2;
		} else {
			return {0, 0};
		}
	}
}
