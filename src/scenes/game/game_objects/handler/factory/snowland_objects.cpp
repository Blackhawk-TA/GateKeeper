//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../characters/enemy.hpp"
#include "../../objects/sign.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_snowland_objects(uint8_t save_id) {
		return {
			new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false),
			new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false),

			new Sign(map::SNOWLAND, Point(11, 13), Sign::WOOD, "The Hospital"),
			new Enemy(map::SNOWLAND, Point(18, 46), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(42, 29), ICE_BEAR, LEFT, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(57, 33), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(42, 5), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(54, 19), ICE_BEAR, UP, save_id, true, "GRR!"),
		};
	}
}
