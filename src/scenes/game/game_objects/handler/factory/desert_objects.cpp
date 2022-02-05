//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_desert_objects(uint8_t save_id) {
		return {
			new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, true),
			new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false),

			new Enemy(map::DESERT, Point(18, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(28, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(34, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(44, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(27, 34), BLUE_GUARD, RIGHT, save_id, true),
			new Enemy(map::DESERT, Point(35, 34), BLUE_GUARD, LEFT, save_id, true),
			new Enemy(map::DESERT, Point(28, 30), BLUE_GUARD, RIGHT, save_id),
			new Enemy(map::DESERT, Point(34, 30), BLUE_GUARD, LEFT, save_id),
			new Enemy(map::DESERT, Point(16, 11), BLUE_GUARD, UP, save_id, true),
			new Enemy(map::DESERT, Point(46, 11), BLUE_GUARD, UP, save_id, true),
		};
	}
}
