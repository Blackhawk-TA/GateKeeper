//
// Created by D069765 on 26.10.2021.
//

#include "game_objects.hpp"
#include "../game_objects/gate_statue.hpp"

std::vector<IGameObject*> game_object_collection;

void game_objects::init() {
	game_object_collection.emplace_back(new GateStatue(map::DUNGEON, Point(14, 22), false));
}

std::vector<IGameObject> game_objects::generate_game_objects(std::vector<Point> &positions, map::MapSections map_section) {
	return {};
}

void game_objects::load() {

}

void game_objects::save() {

}

void game_objects::draw() {
	for (auto &game_object : game_object_collection) {
		game_object->draw();
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
