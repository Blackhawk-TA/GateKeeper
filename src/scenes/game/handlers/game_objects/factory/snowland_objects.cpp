//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../../game_objects/objects/stargate.hpp"
#include "../../../game_objects/characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_snowland_objects(uint8_t save_id) {
		return {
			new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false),
			new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false),

			new Enemy(map::SNOWLAND, Point(18, 46), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(42, 29), ICE_BEAR, LEFT, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(57, 33), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(42, 5), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(54, 19), ICE_BEAR, UP, save_id, true, "GRR!"),
		};
	}
}
