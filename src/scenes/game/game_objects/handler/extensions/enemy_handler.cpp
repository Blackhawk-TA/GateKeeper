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

	void delete_enemy(Signature &signature) {
		auto itr = enemies.begin();

		while (itr != enemies.end()) {
			if (game_objects::has_equal_signature((*itr)->get_signature(), signature)) {
				enemies.erase(itr);
			} else {
				itr++;
			}
		}
	}

	void respawn() {
		auto itr = enemies.begin();
		while (itr != enemies.end()) {
			if ((*itr)->can_be_respawned()) {
				(*itr)->set_active(true);
			} else {
				game_objects::delete_game_object((*itr)->get_signature());
			}
			itr++;
		}
	}
}
