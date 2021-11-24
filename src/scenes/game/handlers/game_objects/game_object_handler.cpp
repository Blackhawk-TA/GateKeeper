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
#include <stdexcept>
#include <cassert>

std::vector<GameObject*> game_object_collection;

void game_objects::init() {
	//Gate statues
	game_object_collection.emplace_back(new GateStatue(map::DUNGEON, Point(14, 22), true));

	//Stargates
	game_object_collection.emplace_back(new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND, WINTER, true));
	game_object_collection.emplace_back(new Stargate(map::SNOWLAND, Point(12, 10), WINTER, GRASSLAND, false));

	//Signs
	game_object_collection.emplace_back(new Sign(map::GRASSLAND, Point(24, 44), Sign::WOOD, "Trees grow fruits which can be eaten. They regrow after harvesting."));
	game_object_collection.emplace_back(new Sign(map::GRASSLAND, Point(25, 12), Sign::WOOD, "The Stargate is a portal to other worlds! It was closed to keep the village safe."));
	game_object_collection.emplace_back(new Sign(map::DUNGEON, Point(15, 23), Sign::STONE, "This dungeon was created to keep the gate closed and protect the world from unknown dangers."));

	//Fruit trees
	game_object_collection.emplace_back(new FruitTree(map::GRASSLAND, Point(11, 16), true));
	game_object_collection.emplace_back(new FruitTree(map::GRASSLAND, Point(21, 42), true));

	//Carrot beds
	game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(16, 42)));
	game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(17, 42)));
	game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(18, 42)));
	game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(16, 43)));
	game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(17, 43)));
	game_object_collection.emplace_back(new CarrotBed(map::GRASSLAND, Point(18, 43)));

	//Salesman character
	game_object_collection.emplace_back(new Salesman(map::INTERIOR, Point(31,20)));

	//Check if GAME_OBJECT_COUNT is set correctly
	assert(GAME_OBJECT_COUNT == game_object_collection.size());

	//Init additional handlers for subclasses with additional functionality
	stargate_handler::init();
}

std::vector<GameObject*> &game_objects::get_collection() {
	return game_object_collection;
}

void game_objects::cleanup() {
	for (auto &game_object : game_object_collection) {
		delete game_object;
		game_object = nullptr;
	}
	game_object_collection.clear();

	//Cleanup extension handlers
	stargate_handler::cleanup();
}

std::array<GameObject::Save, game_objects::GAME_OBJECT_COUNT> game_objects::get_saves() {
	std::array<GameObject::Save, GAME_OBJECT_COUNT> saves;

	for (uint16_t i = 0; i < GAME_OBJECT_COUNT; i++) {
		saves[i] = game_object_collection.at(i)->get_save();
	}

	return saves;
}

void game_objects::load_saves(std::array<GameObject::Save, GAME_OBJECT_COUNT> &saved_objects) {
	GameObject::Signature signature;

	for (auto & saved_object : saved_objects) {
		for (auto &game_object : game_object_collection) {
			signature = game_object->get_signature();

			if (signature.map_section == saved_object.signature.map_section
			&& signature.position == saved_object.signature.position) {
				game_object->load_save(saved_object.data);
			}
		}
	}
}

void game_objects::draw() {
	for (auto &game_object : game_object_collection) {
		if (game_object->is_rendered()) {
			game_object->draw();
		}
	}
}

void game_objects::update(uint32_t time) {
	for (auto &game_object : game_object_collection) {
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
	for (auto &game_object : game_object_collection) {
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

bool game_objects::inventory_interact() {
	bool interacted = false;
	uint16_t i = 0;

	while (!interacted && i < game_object_collection.size()) {
		if (game_object_collection.at(i)->is_rendered()) {
			interacted = game_object_collection.at(i)->inventory_interact();
		}
		i++;
	}

	return interacted;
}

void game_objects::update_states(Point next_position) {
	for (auto &game_object : game_object_collection) {
		if (game_object->is_rendered()) {
			game_object->update_state(next_position);
		}
	}
}
