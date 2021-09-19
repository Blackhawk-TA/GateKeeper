//
// Created by daniel on 18.09.21.
//

#include "stargate_handler.hpp"
#include "../game_objects/stargate.hpp"

//TODO check if map makes sense here or vector is better, it is planned to use key as address selector later on
std::map<stargate_handler::Stargates, Stargate *> stargates;
std::map<stargate_handler::Stargates, Stargate *>::iterator it;

void stargate_handler::init() {
	stargates.insert(std::make_pair(GRASSLAND, new Stargate(map::GRASSLAND, WINTER, Point(21, 7), true)));
	stargates.insert(std::make_pair(WINTER, new Stargate(map::GRASSLAND, GRASSLAND, Point(21, 15), true)));
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

void stargate_handler::update_states(Point next_position) {
	for (const auto& [key, stargate] : stargates) {
		stargate->update_state(next_position);
	}
}

/**
 * Checks if the players next position triggers a teleportation and returns the destination, if existing
 * @param next_position The next position of the player
 * @return The position of the destination gate if there is one, else Point(0, 0) is returned
 */
Point stargate_handler::get_teleport_destination(Point next_position) {
	bool teleport = false;
	Stargates destination_gate;
	Point destination = Point(0, 0);

	//Check if player entered a gate
	while (!teleport && it != stargates.end()) {
		teleport = it->second->check_enter(next_position);
		if (!teleport) {
			it++;
		}
	}

	if (teleport) {
		bool destination_found = false;
		destination_gate = it->second->get_destination();

		//Find destination of entered gate
		it = stargates.begin(); //Reset iterator
		while (!destination_found && it != stargates.end()) {
			if (it->first == destination_gate) {
				destination_found = true;
			} else {
				it++;
			}
		}

		//Trigger teleport with transition and set camera position
		if (destination_found) {
			destination = it->second->get_entry_point();
		}
	}
	it = stargates.begin(); //Reset iterator

	return destination;
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
