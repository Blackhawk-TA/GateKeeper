//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../../game_objects/objects/stargate.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_snowland_objects(uint8_t save_id) {
		return {
			new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false),
			new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false),
		};
	}
}
