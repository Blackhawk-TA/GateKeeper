//
// Created by daniel on 07.09.22.
//

#include "object_factory.hpp"
#include "../../objects/chest.hpp"
#include "../../objects/crystal.hpp"
#include "../../characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_water_dungeon_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Chest(map::WATER_DUNGEON, Point(24, 24)),
			new Chest(map::WATER_DUNGEON, Point(40, 24)),
			new Crystal(map::WATER_DUNGEON, Point(32, 24), Crystal::YELLOW),
			new Enemy(map::WATER_DUNGEON, Point(18, 50), 81, SPIDER, RIGHT, save_id, false),
			new Enemy(map::WATER_DUNGEON, Point(46, 50), 82, SPIDER, LEFT, save_id, false),
			new Enemy(map::WATER_DUNGEON, Point(32, 38), 91, SPIDER, DOWN, save_id, true),
			new Enemy(map::WATER_DUNGEON, Point(32, 30), 91, SPIDER, DOWN, save_id, true),
			new Enemy(map::WATER_DUNGEON, Point(29, 26), 100, SPIDER, RIGHT, save_id, false),
			new Enemy(map::WATER_DUNGEON, Point(35, 26), 100, SPIDER, LEFT, save_id, false),
		};
	}
}