//
// Created by daniel on 06.09.21.
//
#include "building.hpp"

/**
 * Gets the id of a building by the position of its interior or exterior door depending on
 * @param p The position on the map
 * @param map_section The section type of the current tile map
 * @return The id of the building. If value is 255, no building was found
 */
uint8_t building::get_id(Point &p, map::MapSections map_section) {
	uint8_t id = 255; //Value 255 represents 'no building found'
	uint8_t i = 0;

	while (id == 255 && i < sizeof(connections) / sizeof(connections[0])) {
		if ((map_section == map::MapSections::INTERIOR && connections[i].interior == p) ||
			(map_section != map::MapSections::INTERIOR && connections[i].exterior == p))
		{
			id = i;
		}
		i++;
	}

	return id;
}
