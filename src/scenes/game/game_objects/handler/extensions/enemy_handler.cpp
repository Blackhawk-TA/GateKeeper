//
// Created by daniel on 25.02.22.
//

#include "enemy_handler.hpp"
#include "../game_object_handler.hpp"

namespace game::enemy_handler {
	std::vector<Enemy *> enemies;

	void init() {
		std::vector<GameObject *> game_object_collection = game_objects::get_collection();

		for (GameObject *game_object: game_object_collection) {
			if (game_object->get_type() == GameObject::EnemyType) {
				enemies.push_back((Enemy *) game_object);
			}
		}
	}

	void cleanup() {
		enemies.clear();
	}

	void respawn() {
		for (Enemy *enemy : enemies) {
			enemy->set_active(true);
		}
	}
}
