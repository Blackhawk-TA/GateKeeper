//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../../game_objects/objects/stargate.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_desert_objects(uint8_t save_id) {
		return {
			new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, true),
			new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false),
		};
	}
}
