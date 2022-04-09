//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../characters/enemy.hpp"
#include "../../objects/gate_statue.hpp"
#include "../../objects/crystal.hpp"
#include "../../objects/chest.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_volcano_objects(uint8_t save_id, StoryState story_state) {
		std::vector<GameObject*> objects = {};
		std::array<CombatCharacterType, 3> enemies = {SPIDER, RED_CREATURE, DEVIL};

		return {
			new GateStatue(map::VOLCANO, Point(14, 13)),
			new Crystal(map::VOLCANO, Point(48, 5), Crystal::RED),
			new Enemy(map::VOLCANO, Point(21, 50), 8, enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(48, 45), 8, enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(60, 32), 8, enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(26, 37), 8, enemies[blit::random() % enemies.size()], UP, save_id, false),
			new Enemy(map::VOLCANO, Point(3, 47), 8, enemies[blit::random() % enemies.size()], UP, save_id, false),
			new Enemy(map::VOLCANO, Point(11, 28), 8, enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(39, 24), 8, enemies[blit::random() % enemies.size()], LEFT, save_id, false),
			new Enemy(map::VOLCANO, Point(58, 17), 8, enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(32, 11), 8, enemies[blit::random() % enemies.size()], DOWN, save_id, false),

			new Chest(map::VOLCANO, Point(2, 142)),
			new Chest(map::VOLCANO, Point(16, 14)),
			new Chest(map::VOLCANO, Point(25, 35)),
			new Chest(map::VOLCANO, Point(46, 5)),
		};
	}
}
