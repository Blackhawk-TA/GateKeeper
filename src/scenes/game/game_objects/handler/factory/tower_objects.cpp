//
// Created by daniel on 07.09.22.
//

#include "object_factory.hpp"
#include "../../objects/chest.hpp"
#include "../../objects/crystal.hpp"
#include "../../characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_tower_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Chest(map::TOWER, Point(4, 22)),
			new Chest(map::TOWER, Point(26, 6)),
			new Crystal(map::TOWER, Point(25, 19), Crystal::BLUE),
			new Enemy(map::TOWER, Point(27, 6), 63, SPIDER, DOWN, save_id, true),
			new Enemy(map::TOWER, Point(4, 23), 65, SPIDER, DOWN, save_id, true),
			new Enemy(map::TOWER, Point(6, 21), 70, SPIDER, RIGHT, save_id, true),
			new Enemy(map::TOWER, Point(26, 23), 85, SPIDER, DOWN, save_id, true),
		};
	}
}