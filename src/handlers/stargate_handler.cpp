//
// Created by daniel on 18.09.21.
//

#include "stargate_handler.hpp"
#include "../game_objects/stargate.hpp"

//TODO check if map makes sense here or vector is better, it is planned to use key as address selector later on
std::map<stargate_handler::Stargates, Stargate *> stargates;
std::map<stargate_handler::Stargates, Stargate *>::iterator it;

void stargate_handler::init() {
	stargates.insert(std::make_pair(GRASSLAND, new Stargate(Point(21, 7), Point(0, 0), true)));
	it = stargates.begin();
}

bool stargate_handler::check_collisions(Point next_position) {
	bool collision = false;

	while (!collision && it != stargates.end()) {
		collision = it->second->check_collision(next_position);
		it++;
	}

	it = stargates.begin(); //Reset iterator

	return collision;
}

void stargate_handler::check_activations(Point next_position) {
	for (const auto& [key, stargate] : stargates) {
		stargate->check_activation(next_position);
	}
}

void stargate_handler::check_enter(Point next_position) {
	for (const auto& [key, stargate] : stargates) {
		stargate->check_enter(next_position);
	}
}

void stargate_handler::draw_stargates() {
	for (const auto& [key, stargate] : stargates) {
		stargate->draw();
	}
}

void stargate_handler::update_animations() {
	for (const auto& [key, stargate] : stargates) {
		stargate->update_animation();
	}
}
