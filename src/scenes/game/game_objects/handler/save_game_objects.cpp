//
// Created by daniel on 27.02.22.
//

#include "save_game_objects.hpp"
#include "game_object_handler.hpp"
#include "../../../../utils/saves/save_types.hpp"
#include "extensions/enemy_handler.hpp"
#include "extensions/stargate_handler.hpp"
#include "player_handler.hpp"

namespace game::game_objects {
	void load_saves(std::array<GameObject::Save, MAX_GAME_OBJECTS> &saved_objects, StoryState story_state) {
		Signature signature{};
		GameObject::Save *saved_object;
		uint8_t i = 0;
		bool array_end = false;

		while (!array_end && i < MAX_GAME_OBJECTS) {
			saved_object = &saved_objects[i];

			if (is_empty_signature(saved_object->signature)) {
				array_end = true;
				continue;
			}

			for (auto &game_object: get_collection()) {
				signature = game_object->get_signature();

				if (has_equal_signature(signature, saved_object->signature)) {
					game_object->load_save(saved_object->data);
				}
			}
			i++;
		}

		//Respawn enemies
		SceneType previous_scene = get_previous_scene();
		if (previous_scene == SceneType::MENU || previous_scene == SceneType::GAMEOVER) {
			enemy_handler::respawn();
		}

		//Damage stargate
		if (story_state == StoryState::FIRST_HOSPITAL_WAKEUP) {
			Signature gate_signature = {
				map::GRASSLAND,
				21,
				7,
			};
			stargate_handler::damage_stargate(gate_signature);
			player_handler::next_story_state();
		}
	}

	std::array<GameObject::Save, MAX_GAME_OBJECTS> get_section_saves() {
		std::array<GameObject::Save, MAX_GAME_OBJECTS> saves = {};

		for (uint8_t i = 0; i < get_collection().size(); i++) {
			saves[i] = get_collection().at(i)->get_save();
		}

		return saves;
	}

	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> get_global_saves(uint8_t save_id) {
		//The game object data which is currently in memory from the current map section
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> current_game_objects = get_section_saves();

		//Load old save to fetch game object data that is not currently in memory
		save::SaveData old_save = {};
		bool save_found = read_save(old_save, save_id);
		bool game_object_save_exists;
		uint8_t i;

		if (save_found) {
			for (auto &current_game_object : current_game_objects) {
				if (is_empty_signature(current_game_object.signature)) {
					continue;
				}

				game_object_save_exists = false;
				i = 0;

				//Update existing game object save if it exists
				while (!game_object_save_exists && i < old_save.game_objects.size()) {
					if (has_equal_signature(old_save.game_objects.at(i).signature, current_game_object.signature)) {
						old_save.game_objects.at(i) = current_game_object;
						game_object_save_exists = true;
					}
					i++;
				}

				//Add new game object save to existing save
				if (!game_object_save_exists) {
					for (auto &old_game_object: old_save.game_objects) {
						if (is_empty_signature(old_game_object.signature)) {
							old_game_object = current_game_object;
							break;
						}
					}
				}
			}
		} else {
			old_save.game_objects = current_game_objects;
		}

		//Return overwritten game objects
		return old_save.game_objects;
	}
}
