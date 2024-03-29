//
// Created by daniel on 24.11.21.
//

#include "character_handler.hpp"
#include "../game_object_handler.hpp"

namespace game {
	std::vector<Character *> characters = {};
	Timer *animation_timer;

	void character_handler::init() {
		std::vector<GameObject *> game_object_collection = game_objects::get_collection();

		for (GameObject *game_object: game_object_collection) {
			if (game_object->get_type() == GameObject::CharacterType || game_object->get_type() == GameObject::EnemyType) {
				characters.push_back((Character *) game_object);
			}
		}

		animation_timer = new Timer();
		animation_timer->init(animate, 150, -1);
		animation_timer->start();
	}

	void character_handler::delete_character(Signature &signature) {
		auto itr = characters.begin();

		while (itr != characters.end()) {
			if (game_objects::has_equal_signature((*itr)->get_signature(), signature)) {
				characters.erase(itr);
				break;
			} else {
				itr++;
			}
		}
	}

	void character_handler::cleanup() {
		if (animation_timer != nullptr) {
			animation_timer->stop();
			delete animation_timer;
		}

		characters.clear();
	}

	void character_handler::animate(Timer &timer) {
		for (Character *character: characters) {
			if (character->is_rendered()) {
				character->animate();
			}
		}
	}
}
