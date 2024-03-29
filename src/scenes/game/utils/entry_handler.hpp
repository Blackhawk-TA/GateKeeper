//
// Created by daniel on 02.09.21.
//

#pragma once
#include "../../../utils/utils.hpp"
#include "../../../engine/map.hpp"
#include "../../../utils/types.hpp"

using namespace blit;

/**
 * Connects the entries with their interior by linking the coordinates on the specific tile maps.
 */
namespace game::entry_handler {
	struct Entry {
		Point exterior;
		Point interior;
		Point interior_offset;
		map::MapSection exterior_map;
		map::MapSection interior_map;
	};

	constexpr Entry connections[] = {
		//Grassland houses
		Entry{Point(29, 12), Point(28, 9), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(18, 19), Point(50, 9), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(27, 19), Point(6, 26), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(12, 44), Point(28, 26), Point(0, 1), map::GRASSLAND, map::INTERIOR},
		Entry{Point(15, 12), Point(50, 26), Point(0, 1), map::GRASSLAND, map::INTERIOR},

		//Dungeon entries
		Entry{Point(52, 50), Point(19, 56), Point(1, 0), map::GRASSLAND, map::DUNGEON},
		Entry{Point(13, 28), Point(58, 22), Point(0, 1), map::GRASSLAND, map::DUNGEON},
		Entry{Point(56, 15), Point(33, 61), Point(1, 0), map::SNOWLAND, map::VOLCANO},
		Entry{Point(54, 49), Point(33, 53), Point(1, 0), map::SNOWLAND, map::WATER_DUNGEON},

		//Snowland houses
		Entry{Point(19, 13), Point(6, 43), Point(0, 1), map::SNOWLAND, map::INTERIOR},
		Entry{Point(28, 13), Point(28, 43), Point(0, 1), map::SNOWLAND, map::INTERIOR},
		Entry{Point(14, 13), Point(50, 43), Point(0, 1), map::SNOWLAND, map::INTERIOR},
		Entry{Point(13, 20), Point(6, 60), Point(0, 1), map::SNOWLAND, map::INTERIOR},
		Entry{Point(24, 20), Point(28, 60), Point(0, 1), map::SNOWLAND, map::INTERIOR},

		//Castle
		Entry{Point(31, 28), Point(15, 30), Point(0, 1), map::DESERT, map::CASTLE},

		//Grassland tower
		Entry{Point(50,28), Point(4, 8), Point(0, 0), map::GRASSLAND, map::TOWER},
		Entry{Point(6, 2), Point(28, 2), Point(0, 0), map::TOWER, map::TOWER},
		Entry{Point(25, 2), Point(3, 19), Point(0, 0), map::TOWER, map::TOWER},
		Entry{Point(6, 19), Point(28, 19), Point(0, 0), map::TOWER, map::TOWER},
	};

	/**
	 * Gets the id of an entry by the position of its interior or exterior entry depending on
	 * @param p The position on the map
	 * @param current_map The section type of the current tile map
	 * @return The id of the entry. If value is 255, no entry was found
	 */
	uint8_t get_id(Point &p, map::MapSection current_map);

	/**
	 * Teleports the player to the interior/exterior of the entry and swaps the tile maps
	 * @param entry_id The id of the entry
	 * @param next_position The position where the player will walk within the next move
	 * @param save_id The id of the current save
	 * @param story_state The current state of the story
	 */
	void teleport(uint8_t entry_id, Point next_position, uint8_t save_id, StoryState story_state);

	/**
	 * Triggers the entering process of for example a door or dungeon
	 * @param next_position The position where the player will walk within the next move
	 * @param save_id The id of the current save
	 * @param story_state The current state of the story
	 * @return False if entry id was not found, else true
	 */
	bool enter(Point &next_position, uint8_t save_id, StoryState story_state);
}
