//
// Created by daniel on 06.09.21.
//
#include "entry_handler.hpp"
#include "../engine/camera.hpp"
#include "../engine/transition.hpp"

/**
 * Gets the id of an entry by the position of its interior or exterior entry depending on
 * @param p The position on the map
 * @param current_map The section type of the current tile map
 * @return The id of the entry. If value is 255, no entry was found
 */
uint8_t entry_handler::get_id(Point &p, map::MapSections current_map) {
	uint8_t id = 255; //Value 255 represents 'no entry found'
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

/**
 * Teleports the player to the interior/exterior of the entry and swaps the tile maps
 * @param entry_id The id of the entry
 * @param next_position The position where the player will walk within the next move
 */
void entry_handler::teleport(uint8_t entry_id, Point next_position) {
	Point destination;
	entry_handler::Entry entry = entry_handler::connections[entry_id];

	if (next_position == entry.exterior) {
		map::load_section(entry.interior_map);
		destination = entry.interior - entry.interior_offset;
	} else if (next_position == entry.interior) {
		map::load_section(entry.exterior_map);
		destination = entry.exterior + Point(0, 1); //On exit teleport player in front of the door instead of directly on it
	}

	camera::set_position(destination);
}

/**
 * Triggers the entering process of for example a door or dungeon
 * @param next_position The position where the player will walk within the next move
 * @return False if entry id was not found, else true
 */
bool entry_handler::enter(Point &next_position) {
	uint8_t entry_id = entry_handler::get_id(next_position, map::get_section());

	//No entry found, stop movement
	if (entry_id == 255) {
		return false;
	}

	//Teleport to position on different tile map
	transition::start([entry_id, next_position] {
		entry_handler::teleport(entry_id, next_position);
	});

	return true;
}
