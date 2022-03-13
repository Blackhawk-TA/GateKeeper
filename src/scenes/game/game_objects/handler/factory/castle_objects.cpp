//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_castle_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Enemy(map::CASTLE, Point(12, 14), BLUE_GUARD, RIGHT, save_id),
			new Enemy(map::CASTLE, Point(13, 17), BLUE_GUARD, RIGHT, save_id),
			new Enemy(map::CASTLE, Point(13, 20), BLUE_GUARD, RIGHT, save_id),
			new Enemy(map::CASTLE, Point(13, 23), BLUE_GUARD, RIGHT, save_id),
			new Enemy(map::CASTLE, Point(18, 14), BLUE_GUARD, LEFT, save_id),
			new Enemy(map::CASTLE, Point(17, 17), BLUE_GUARD, LEFT, save_id),
			new Enemy(map::CASTLE, Point(17, 20), BLUE_GUARD, LEFT, save_id),
			new Enemy(map::CASTLE, Point(17, 23), BLUE_GUARD, LEFT, save_id),
		};
	}
}
