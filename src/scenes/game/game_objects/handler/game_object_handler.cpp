//
// Created by D069765 on 26.10.2021.
//

#include "game_object_handler.hpp"
#include "extensions/stargate_handler.hpp"
#include "extensions/dungeon_door_handler.hpp"
#include "extensions/character_handler.hpp"
#include "factory/object_factory.hpp"
#include <stdexcept>
#include <cassert>

namespace game::game_objects {
	std::vector<GameObject *> game_object_collection;

	void init(map::MapSection map_section, uint8_t save_id) {
		game_object_collection = create_game_objects(map_section, save_id);
		assert(game_object_collection.size() <= MAX_GAME_OBJECTS);

		//Init additional handlers for subclasses with additional functionality
		stargate_handler::init();
		dungeon_door_handler::init();
		character_handler::init();
	}

	std::vector<GameObject *> &get_collection() {
		return game_object_collection;
	}

	void delete_game_object(Signature &signature) {
		auto itr = game_object_collection.begin();

		while (itr != game_object_collection.end()) {
			if (has_equal_signature((*itr)->get_signature(), signature)) {
				switch((*itr)->get_type()) {
					case GameObject::StargateType:
						stargate_handler::delete_stargate(signature);
						break;
					case GameObject::CharacterType:
						character_handler::delete_character(signature);
						break;
					case GameObject::DungeonDoorType:
						dungeon_door_handler::delete_door(signature);
						break;
					default:
						break;
				}

				delete (*itr);
				(*itr) = nullptr;
				game_object_collection.erase(itr);

				break;
			} else {
				itr++;
			}
		}
	}

	void cleanup() {
		for (auto &game_object: game_object_collection) {
			delete game_object;
			game_object = nullptr;
		}
		game_object_collection.clear();

		//Cleanup extension handlers
		stargate_handler::cleanup();
		dungeon_door_handler::cleanup();
		character_handler::cleanup();
	}

	bool has_equal_signature(Signature sig1, Signature sig2) {
		return sig1.map_section == sig2.map_section && sig1.x == sig2.x && sig1.y == sig2.y;
	}

	bool is_empty_signature(Signature &signature) {
		return signature.map_section == map::NO_MAP && signature.x == 0 && signature.y == 0;
	}

	std::array<GameObject::Save, MAX_GAME_OBJECTS> get_saves() {
		std::array<GameObject::Save, MAX_GAME_OBJECTS> saves = {};

		for (uint8_t i = 0; i < game_object_collection.size(); i++) {
			saves[i] = game_object_collection.at(i)->get_save();
		}

		return saves;
	}

	void load_saves(std::array<GameObject::Save, MAX_GAME_OBJECTS> &saved_objects) {
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

			for (auto &game_object: game_object_collection) {
				signature = game_object->get_signature();

				if (has_equal_signature(signature, saved_object->signature)) {
					game_object->load_save(saved_object->data);
				}
			}
			i++;
		}
	}

	void draw_under_player() {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_drawn_under_player() && game_object->is_rendered()) {
				game_object->draw();
			}
		}
	}

	void draw_over_player() {
		for (auto &game_object: game_object_collection) {
			if (!game_object->is_drawn_under_player() && game_object->is_rendered()) {
				game_object->draw();
			}
		}
	}

	void draw_textbox() {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_rendered()) {
				game_object->draw_textbox();
			}
		}
	}

	void update(uint32_t time) {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_rendered()) {
				game_object->update(time);
			}
		}
	}

	bool is_textbox_open() {
		bool is_open = false;
		uint16_t i = 0;

		while (!is_open && i < game_object_collection.size()) {
			is_open = game_object_collection.at(i)->is_textbox_open();
			i++;
		}

		return is_open;
	}

	bool next_textbox() {
		bool has_next = false;
		uint16_t i = 0;

		while (!has_next && i < game_object_collection.size()) {
			if (game_object_collection.at(i)->is_textbox_open()) {
				has_next = game_object_collection.at(i)->next_textbox();
			}
			i++;
		}

		return has_next;
	}

	void close_textboxes() {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_textbox_open()) {
				game_object->close_textbox();
			}
		}
	}

	bool check_collisions(Point next_position) {
		bool collision = false;
		uint16_t i = 0;

		while (!collision && i < game_object_collection.size()) {
			if (game_object_collection.at(i)->is_rendered()) {
				collision = game_object_collection.at(i)->check_collision(next_position);
			}
			i++;
		}

		return collision;
	}

	bool player_interact() {
		bool interacted = false;
		uint16_t i = 0;

		while (!interacted && i < game_object_collection.size()) {
			if (game_object_collection.at(i)->is_rendered()) {
				interacted = game_object_collection.at(i)->player_interact();
			}
			i++;
		}

		return interacted;
	}

	bool inventory_interact(items::INVENTORY_ITEM item_type) {
		bool interacted = false;
		uint16_t i = 0;

		while (!interacted && i < game_object_collection.size()) {
			if (game_object_collection.at(i)->is_rendered()) {
				interacted = game_object_collection.at(i)->inventory_interact(item_type);
			}
			i++;
		}

		return interacted;
	}

	void update_states(Point next_position) {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_rendered()) {
				game_object->update_state(next_position);
			}
		}
	}
}
