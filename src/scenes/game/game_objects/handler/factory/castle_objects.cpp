//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../characters/enemy.hpp"
#include "../../objects/chest.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_castle_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Enemy(map::CASTLE, Point(12, 14), 15, BLUE_GUARD, RIGHT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(12, 17), 15, BLUE_GUARD, RIGHT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(12, 20), 15, BLUE_GUARD, RIGHT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(12, 23), 15, BLUE_GUARD, RIGHT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(18, 14), 15, BLUE_GUARD, LEFT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(18, 17), 15, BLUE_GUARD, LEFT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(18, 20), 15, BLUE_GUARD, LEFT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(18, 23), 15, BLUE_GUARD, LEFT, save_id, false, "", false),
			new Enemy(map::CASTLE, Point(15, 7),  20, RED_GUARD, DOWN, save_id, false, "You dare challenging me? You will never defeat me!", false),

			new Chest(map::CASTLE, Point(12, 6)),
			new Chest(map::CASTLE, Point(13, 6)),
			new Chest(map::CASTLE, Point(14, 6)),
			new Chest(map::CASTLE, Point(16, 6)),
			new Chest(map::CASTLE, Point(17, 6)),
			new Chest(map::CASTLE, Point(18, 6)),
		};
	}
}
