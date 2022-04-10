//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../characters/enemy.hpp"
#include "../../objects/chest.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_desert_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, true),
			new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false),

			new Enemy(map::DESERT, Point(4, 60), 10, BLUE_GUARD, RIGHT, save_id, false, "Why are you here?", false),
			new Enemy(map::DESERT, Point(5, 62), 10, BLUE_GUARD, UP, save_id, false, "Stop! Who are you?", false),

			//TODO ren-enable this enemy once escape in front of gate is possible
//			new Enemy(map::DESERT, Point(6, 60), 10, BLUE_GUARD, LEFT, save_id, false, "You are not supposed to be here!", false),

			new Enemy(map::DESERT, Point(18, 48), 12, BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(28, 48), 12, BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(34, 48), 12, BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(44, 48), 12, BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(27, 34), 12, BLUE_GUARD, RIGHT, save_id, true, "You are not allowed to be here!"),
			new Enemy(map::DESERT, Point(35, 34), 12, BLUE_GUARD, LEFT, save_id, true, "What are you doing here?"),
			new Enemy(map::DESERT, Point(28, 30), 12, BLUE_GUARD, RIGHT, save_id, false, "I cannot let you pass!"),
			new Enemy(map::DESERT, Point(34, 30), 12, BLUE_GUARD, LEFT, save_id, false, "Run as long as you can!"),
			new Enemy(map::DESERT, Point(16, 11), 12, BLUE_GUARD, UP, save_id, true, "How did you get here?"),
			new Enemy(map::DESERT, Point(46, 11), 12, BLUE_GUARD, UP, save_id, true, "You have no permission to be here!"),
			new Enemy(map::DESERT, Point(30, 53), 14, BLUE_GUARD, RIGHT, save_id, false, "You cannot enter."),
			new Enemy(map::DESERT, Point(32, 53), 14, BLUE_GUARD, LEFT, save_id, false, "I cannot let you through."),
			new Enemy(map::DESERT, Point(29, 42), 14, BLUE_GUARD, RIGHT, save_id, true, "I cannot let you go."),
			new Enemy(map::DESERT, Point(33, 42), 14, BLUE_GUARD, LEFT, save_id, true, "You will pay for intruding here!"),

			new Chest(map::DESERT, Point(2, 50)),
			new Chest(map::DESERT, Point(27, 33)),
			new Chest(map::DESERT, Point(35, 33)),
			new Chest(map::DESERT, Point(48, 32)),
			new Chest(map::DESERT, Point(24, 10)),
		};
	}
}
