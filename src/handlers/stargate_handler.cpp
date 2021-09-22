//
// Created by daniel on 18.09.21.
//

#include "stargate_handler.hpp"

std::map<StargateAddresses, Stargate> stargates;
std::map<StargateAddresses, Stargate>::iterator it;

void stargate_handler::init() {
	stargates.insert(std::make_pair(GRASSLAND, Stargate(map::GRASSLAND, WINTER, Point(21, 7), false)));
	stargates.insert(std::make_pair(WINTER, Stargate(map::SNOWLAND, GRASSLAND, Point(12, 10), false)));
	it = stargates.begin();
}

bool stargate_handler::check_collisions(Point next_position) {
	bool collision = false;

	while (!collision && it != stargates.end()) {
		collision = it->second.check_collision(next_position);
		it++;
	}
	it = stargates.begin(); //Reset iterator

	return collision;
}

void stargate_handler::update_states(Point next_position) {
	for (auto&[key, stargate]: stargates) {
		stargate.update_state(next_position);
	}
}

/**
 * Checks if the players next position triggers a teleportation and returns the destination gate, if existing
 * @param next_position The next position of the player
 * @return The position of the destination gate if there is one, else Point(0, 0) is returned
 */
Stargate *stargate_handler::get_destination_gate(Point next_position) {
	bool teleport = false;
	StargateAddresses destination_address;
	Stargate *destination_gate = nullptr;

	//Check if player entered a gate
	while (!teleport && it != stargates.end()) {
		teleport = it->second.check_enter(next_position);
		if (!teleport) {
			it++;
		}
	}

	//Find destination gate
	if (teleport) {
		destination_address = it->second.get_destination();

		it = stargates.find(destination_address);
		if (it != stargates.end()) {
			destination_gate = &it->second;
		}
	}

	//Reset iterator
	it = stargates.begin();

	return destination_gate;
}

void stargate_handler::draw_stargates() {
	for (auto &[key, stargate]: stargates) {
		stargate.draw();
	}
}

void stargate_handler::update_animations() {
	for (auto &[key, stargate]: stargates) {
		stargate.update_animation();
	}
}
