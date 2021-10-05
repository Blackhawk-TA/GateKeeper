//
// Created by daniel on 06.09.21.
//
#include "entry_registry.hpp"

/**
 * Gets the id of an entry by the position of its interior or exterior entry depending on
 * @param p The position on the map
 * @param current_map The section type of the current tile map
 * @return The id of the building. If value is 255, no building was found
 */
uint8_t entry_registry::get_id(Point &p, map::MapSections current_map) {
	uint8_t id = 255; //Value 255 represents 'no building found'
	uint8_t i = 0;

	while (id == 255 && i < sizeof(connections) / sizeof(connections[0])) {
		if ((current_map == connections[i].interior_map && connections[i].interior == p) ||
		    (current_map == connections[i].exterior_map && connections[i].exterior == p))
		{
			id = i;
		}
		i++;
	}

	return id;
}
