//
// Created by D069765 on 26.10.2021.
//

#include "game_objects.hpp"
#include "../game_objects/gate_statue.hpp"
#include "../game_objects/stargate.hpp"
#include "stargate_handler.hpp"
#include <stdexcept>
#include <cassert>

std::vector<GameObject*> game_object_collection;

void game_objects::init() {
	//Gate statues
	game_object_collection.emplace_back(new GateStatue(map::DUNGEON, Point(14, 22), true));

	//Stargates
	game_object_collection.emplace_back(new Stargate(map::GRASSLAND, GRASSLAND, WINTER, Point(21, 7), true));
	game_object_collection.emplace_back(new Stargate(map::SNOWLAND, WINTER, GRASSLAND, Point(12, 10), true));

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
	}
	game_object_collection.clear();
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
				game_object->load_save(saved_object.value);
			}
		}
	}
}

void game_objects::draw() {
	for (auto &game_object : game_object_collection) {
		game_object->draw();
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
		collision = game_object_collection.at(i)->check_collision(next_position);
		i++;
	}

	return collision;
}

bool game_objects::interact() {
	bool interacted = false;
	uint16_t i = 0;

	while (!interacted && i < game_object_collection.size()) {
		interacted = game_object_collection.at(i)->interact();
		i++;
	}

	return interacted;
}

void game_objects::update_states(Point next_position) {
	for (auto &game_object : game_object_collection) {
		game_object->update_state(next_position);
	}
}
