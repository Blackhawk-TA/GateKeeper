//
// Created by D069765 on 26.10.2021.
//

#include "game_object_handler.hpp"
#include "../../game_objects/objects/gate_statue.hpp"
#include "../../game_objects/objects/stargate.hpp"
#include "extensions/stargate_handler.hpp"
#include "../../game_objects/objects/sign.hpp"
#include "../../game_objects/objects/fruit_tree.hpp"
#include "../../game_objects/objects/carrot_bed.hpp"
#include "../../game_objects/characters/salesman.hpp"
#include "../../game_objects/characters/villager.hpp"
#include "../../game_objects/objects/lever.hpp"
#include "../../game_objects/objects/dungeon_door.hpp"
#include "extensions/dungeon_door_handler.hpp"
#include "../../game_objects/characters/enemy.hpp"
#include "extensions/character_handler.hpp"
#include <stdexcept>
#include <cassert>
#include <iostream>

namespace game {
	std::vector<GameObject *> game_object_collection;

	//TODO move game object creation data to external file, .txt or something similar
	void game_objects::init(map::MapSection map_section, uint8_t save_id) {
		//Settings for dungeon
		uint8_t enabled_lever = blit::random() % 3;
		Signature interaction_signature = { //The signature of the door that the levers open
			map::DUNGEON,
			14,
			36
		};

		//TODO requires save after map section change, and save inserting to the correct array indexes
		switch (map_section) {
			case map::DUNGEON:
				game_object_collection.emplace_back(new GateStatue(map::DUNGEON, Point(14, 22), true));
				game_object_collection.emplace_back(new Sign(map::DUNGEON, Point(15, 23), Sign::STONE, "This dungeon was created to keep the gate closed and protect the village."));
				game_object_collection.emplace_back(new Enemy(map::DUNGEON, Point(36, 36), SPIDER, DOWN, save_id));
				game_object_collection.emplace_back(new Enemy(map::DUNGEON, Point(42, 36), SPIDER, DOWN, save_id));
				game_object_collection.emplace_back(new Enemy(map::DUNGEON, Point(48, 36), SPIDER, DOWN, save_id));
				game_object_collection.emplace_back(new Enemy(map::DUNGEON, Point(11, 35), SPIDER, RIGHT, save_id));
				game_object_collection.emplace_back(new Enemy(map::DUNGEON, Point(18, 35), SPIDER, LEFT, save_id));
				game_object_collection.emplace_back(new DungeonDoor( static_cast<map::MapSection>(interaction_signature.map_section), Point(interaction_signature.x, interaction_signature.y)));
				game_object_collection.emplace_back(new Lever(map::DUNGEON, Point(37, 36), interaction_signature, enabled_lever == 0));
				game_object_collection.emplace_back(new Lever(map::DUNGEON, Point(43, 36), interaction_signature, enabled_lever == 1));
				game_object_collection.emplace_back(new Lever(map::DUNGEON, Point(49, 36), interaction_signature, enabled_lever == 2));
				break;
			case map::GRASSLAND:
				game_object_collection.emplace_back(new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, true));
				game_object_collection.emplace_back(new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false));
				game_object_collection.emplace_back(new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false));
				game_object_collection.emplace_back(new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false));

				game_object_collection.emplace_back(new Sign(map::GRASSLAND, Point(24, 44), Sign::WOOD, "Trees grow fruits which can be eaten. They regrow after harvesting. Carrots can be planted and harvested."));
				game_object_collection.emplace_back(new Sign(map::GRASSLAND, Point(25, 12), Sign::WOOD, "The Stargate is a portal to other worlds! It was closed to keep the village safe."));
				game_object_collection.emplace_back(new Sign(map::GRASSLAND, Point(24, 19), Sign::WOOD, "Your house"));
				game_object_collection.emplace_back(new Sign(map::GRASSLAND, Point(18, 12), Sign::WOOD, "The Hospital"));
				game_object_collection.emplace_back(new FruitTree(map::GRASSLAND, Point(11, 16), true));
				game_object_collection.emplace_back(new FruitTree(map::GRASSLAND, Point(21, 42), true));
				game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(16, 42)));
				game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(17, 42)));
				game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(18, 42)));
				game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(16, 43)));
				game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(17, 43)));
				game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(18, 43)));
				game_object_collection.emplace_back(new Villager(map::GRASSLAND, Point(24, 15), 0, LEFT, "Hello there!"));
				game_object_collection.emplace_back(new Villager(map::GRASSLAND, Point(13, 14), 12, RIGHT, "Hello I'm the elder of this village."));
//				game_object_collection.emplace_back(new Villager(map::GRASSLAND, Point(39, 17), 4, Character::RIGHT, "There is a Gate in this forest, but I can't let you pass without permission of the elder. It could be too dangerous for you."));
				game_object_collection.emplace_back(new Enemy(map::GRASSLAND, Point(22, 14), BLUE_GUARD, DOWN, save_id, false, "LET'S FIGHT!"));
				break;
			case map::INTERIOR:
				game_object_collection.emplace_back(new Salesman(map::INTERIOR, Point(31, 20)));
				break;
			case map::SNOWLAND:
				game_object_collection.emplace_back(new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false));
				game_object_collection.emplace_back(new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false));
				break;
			case map::DESERT:
				game_object_collection.emplace_back(new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, true));
				game_object_collection.emplace_back(new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false));
				break;
			default:
				std::cerr << "Invalid map section" << std::endl;
				exit(1);
		}

		assert(game_object_collection.size() <= MAX_GAME_OBJECTS);

		//Init additional handlers for subclasses with additional functionality
		stargate_handler::init();
		dungeon_door_handler::init();
		character_handler::init();
	}

	std::vector<GameObject *> &game_objects::get_collection() {
		return game_object_collection;
	}

	void game_objects::delete_game_object(Signature &signature) {
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

	void game_objects::cleanup() {
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

	bool game_objects::has_equal_signature(Signature sig1, Signature sig2) {
		return sig1.map_section == sig2.map_section && sig1.x == sig2.x && sig1.y == sig2.y;
	}

	bool game_objects::is_empty_signature(Signature &signature) {
		return signature.map_section == map::NO_MAP && signature.x == 0 && signature.y == 0;
	}

	std::array<GameObject::Save, MAX_GAME_OBJECTS> game_objects::get_saves() {
		std::array<GameObject::Save, MAX_GAME_OBJECTS> saves = {};

		for (uint8_t i = 0; i < game_object_collection.size(); i++) {
			saves[i] = game_object_collection.at(i)->get_save();
		}

		return saves;
	}

	void game_objects::load_saves(std::array<GameObject::Save, MAX_GAME_OBJECTS> &saved_objects) {
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

	void game_objects::draw_under_player() {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_drawn_under_player() && game_object->is_rendered()) {
				game_object->draw();
			}
		}
	}

	void game_objects::draw_over_player() {
		for (auto &game_object: game_object_collection) {
			if (!game_object->is_drawn_under_player() && game_object->is_rendered()) {
				game_object->draw();
			}
		}
	}

	void game_objects::draw_textbox() {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_rendered()) {
				game_object->draw_textbox();
			}
		}
	}

	void game_objects::update(uint32_t time) {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_rendered()) {
				game_object->update(time);
			}
		}
	}

	bool game_objects::is_textbox_open() {
		bool is_open = false;
		uint16_t i = 0;

		while (!is_open && i < game_object_collection.size()) {
			is_open = game_object_collection.at(i)->is_textbox_open();
			i++;
		}

		return is_open;
	}

	void game_objects::close_textboxes() {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_textbox_open()) {
				game_object->close_textbox();
			}
		}
	}

	bool game_objects::check_collisions(Point next_position) {
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

	bool game_objects::player_interact() {
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

	bool game_objects::inventory_interact(listbox_item::INVENTORY_ITEM item_type) {
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

	void game_objects::update_states(Point next_position) {
		for (auto &game_object: game_object_collection) {
			if (game_object->is_rendered()) {
				game_object->update_state(next_position);
			}
		}
	}
}