//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_desert_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, true),
			new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false),

			new Enemy(map::DESERT, Point(4, 60), BLUE_GUARD, RIGHT, save_id, false, "Why are you here?", false),
			new Enemy(map::DESERT, Point(6, 60), BLUE_GUARD, LEFT, save_id, false, "You are not supposed to be here!", false),

			new Enemy(map::DESERT, Point(18, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(28, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(34, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(44, 48), BLUE_GUARD, DOWN, save_id),
			new Enemy(map::DESERT, Point(27, 34), BLUE_GUARD, RIGHT, save_id, true, "You are not allowed to be here!"),
			new Enemy(map::DESERT, Point(35, 34), BLUE_GUARD, LEFT, save_id, true, "What are you doing here?"),
			new Enemy(map::DESERT, Point(28, 30), BLUE_GUARD, RIGHT, save_id, false, "I cannot let you pass!"),
			new Enemy(map::DESERT, Point(34, 30), BLUE_GUARD, LEFT, save_id, false, "Run as long as you can!"),
			new Enemy(map::DESERT, Point(16, 11), BLUE_GUARD, UP, save_id, true, "How did you get here?"),
			new Enemy(map::DESERT, Point(46, 11), BLUE_GUARD, UP, save_id, true, "You have no permission to be here!"),
			new Enemy(map::DESERT, Point(30, 53), BLUE_GUARD, RIGHT, save_id, false, "You cannot enter."),
			new Enemy(map::DESERT, Point(32, 53), BLUE_GUARD, LEFT, save_id, false, "I cannot let you through."),
			new Enemy(map::DESERT, Point(29, 42), BLUE_GUARD, RIGHT, save_id, true, "I cannot let you go."),
			new Enemy(map::DESERT, Point(33, 42), BLUE_GUARD, LEFT, save_id, true, "You will pay for intruding here!"),
		};
	}
}
