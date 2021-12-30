//
// Created by daniel on 06.09.21.
//
#include "entry_handler.hpp"
#include "../../../engine/effects/transition.hpp"
#include "../player.hpp"
#include "../utils/utils.hpp"

namespace game {
	/**
	 * Gets the id of an entry by the position of its interior or exterior entry depending on
	 * @param p The position on the map
	 * @param current_map The section type of the current tile map
	 * @return The id of the entry. If value is 255, no entry was found
	 */
	uint8_t entry_handler::get_id(Point &p, map::MapSection current_map) {
		uint8_t id = 255; //Value 255 represents 'no entry found'
		uint8_t i = 0;

		while (id == 255 && i < sizeof(connections) / sizeof(connections[0])) {
			if ((current_map == connections[i].interior_map && connections[i].interior == p) ||
			    (current_map == connections[i].exterior_map && connections[i].exterior == p)) {
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
	 * @param save_id The id of the current save
	 */
	void entry_handler::teleport(uint8_t entry_id, Point next_position, uint8_t save_id) {
		map::MapSection destination_map;
		Point destination_position;
		MovementDirection player_direction;
		entry_handler::Entry entry = entry_handler::connections[entry_id];

		if (next_position == entry.exterior) {
			destination_map = entry.interior_map;
			destination_position = entry.interior - entry.interior_offset;
			player_direction = MovementDirection::UP;
		} else {
			destination_map = entry.exterior_map;
			destination_position = entry.exterior + Point(0, 1); //On exit teleport player in front of the door instead of directly on it
			player_direction = MovementDirection::DOWN;
		}

		utils::teleport_player(destination_map, destination_position, player_direction, save_id);
	}

	/**
	 * Triggers the entering process of for example a door or dungeon
	 * @param next_position The position where the player will walk within the next move
	 * @param save_id The id of the current save
	 * @return False if entry id was not found, else true
	 */
	bool entry_handler::enter(Point &next_position, uint8_t save_id) {
		uint8_t entry_id = entry_handler::get_id(next_position, map::get_section());

		//No entry found, stop movement
		if (entry_id == 255) {
			return false;
		}

		//Teleport to position on different tile map
		transition::start([entry_id, next_position, save_id] {
			entry_handler::teleport(entry_id, next_position, save_id);
		});

		return true;
	}
}