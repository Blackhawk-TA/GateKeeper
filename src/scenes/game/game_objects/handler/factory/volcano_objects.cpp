//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../characters/enemy.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_volcano_objects(uint8_t save_id) {
		std::vector<GameObject*> objects = {};
		std::array<CombatCharacterType, 3> enemies = {SPIDER, RED_CREATURE, DEVIL};

		return {
			new Enemy(map::VOLCANO, Point(21, 50), enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(48, 45), enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(60, 32), enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(26, 37), enemies[blit::random() % enemies.size()], UP, save_id, false),
			new Enemy(map::VOLCANO, Point(3, 47), enemies[blit::random() % enemies.size()], UP, save_id, false),
			new Enemy(map::VOLCANO, Point(11, 28), enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(39, 24), enemies[blit::random() % enemies.size()], LEFT, save_id, false),
			new Enemy(map::VOLCANO, Point(58, 17), enemies[blit::random() % enemies.size()], DOWN, save_id, false),
			new Enemy(map::VOLCANO, Point(32, 11), enemies[blit::random() % enemies.size()], DOWN, save_id, false),
		};
	}
}
