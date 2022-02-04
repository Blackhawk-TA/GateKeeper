//
// Created by daniel on 23.01.22.
//

#pragma once
#include "../../template/game_object.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_game_objects(map::MapSection map_section, uint8_t save_id);

	std::vector<GameObject*> create_desert_objects(uint8_t save_id);
	std::vector<GameObject*> create_dungeon_objects(uint8_t save_id);
	std::vector<GameObject*> create_grassland_objects(uint8_t save_id);
	std::vector<GameObject*> create_interior_objects(uint8_t save_id);
	std::vector<GameObject*> create_snowland_objects(uint8_t save_id);
	std::vector<GameObject*> create_volcano_objects(uint8_t save_id);
}
