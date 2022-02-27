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
		std::vector<Enemy*> delete_queue = {};
		auto itr = enemies.begin();

		while (itr != enemies.end()) {
			if ((*itr)->can_be_respawned()) {
				(*itr)->set_active(true);
			} else if (!(*itr)->is_active()){
				delete_queue.push_back(*itr);
			}

			itr++;
		}

		//Use delete queue because deleting in loop while external function delete elements may cause issues
		for(auto &enemy : delete_queue) {
			game_objects::delete_game_object(enemy->get_signature());
		}
		delete_queue.clear();
	}
}
