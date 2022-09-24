//
// Created by daniel on 23.01.22.
//

#include <iostream>
#include "object_factory.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_game_objects(map::MapSection map_section, uint8_t save_id, StoryState story_state) {
		switch (map_section) {
			case map::DUNGEON:
				return create_dungeon_objects(save_id, story_state);
			case map::GRASSLAND:
				return create_grassland_objects(save_id, story_state);
			case map::INTERIOR:
				return create_interior_objects(save_id, story_state);
			case map::SNOWLAND:
				return create_snowland_objects(save_id, story_state);
			case map::DESERT:
				return create_desert_objects(save_id, story_state);
			case map::VOLCANO:
				return create_volcano_objects(save_id, story_state);
			case map::CASTLE:
				return create_castle_objects(save_id, story_state);
			case map::TOWER:
				return create_tower_objects(save_id, story_state);
			case map::WATER_DUNGEON:
				return create_water_dungeon_objects(save_id, story_state);
			default:
				std::cerr << "Invalid map section" << std::endl;
				exit(1);
		}
	}
}
