//
// Created by daniel on 06.09.21.
//
#include "entry_handler.hpp"
#include "../../../engine/effects/transition.hpp"
#include "utils.hpp"

namespace game {
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

	void entry_handler::teleport(uint8_t entry_id, Point next_position, uint8_t save_id, StoryState story_state) {
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

		utils::teleport_player(destination_map, destination_position, player_direction, save_id, story_state);
	}

	bool entry_handler::enter(Point &next_position, uint8_t save_id, StoryState story_state) {
		uint8_t entry_id = entry_handler::get_id(next_position, map::get_section());

		//No entry found, stop movement
		if (entry_id == 255) {
			return false;
		}

		//Teleport to position on different tile map
		transition::start([entry_id, next_position, save_id, story_state] {
			entry_handler::teleport(entry_id, next_position, save_id, story_state);
		});

		return true;
	}
}