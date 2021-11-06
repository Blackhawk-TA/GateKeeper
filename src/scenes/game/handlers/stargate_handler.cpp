//
// Created by daniel on 18.09.21.
//

#include "stargate_handler.hpp"
#include "game_objects.hpp"

std::vector<Stargate*> stargates;

void stargate_handler::init() {
	std::vector<GameObject*> game_object_collection = game_objects::get_collection();

	for (GameObject* game_object : game_object_collection) {
		if (game_object->get_type() == GameObject::StargateType) {
			stargates.push_back((Stargate*)game_object);
		}
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
	uint16_t i = 0;

	//Check if player entered a gate
	while (!teleport && i < stargates.size()) {
		teleport = stargates[i]->check_enter(next_position);
		if (!teleport) {
			i++;
		}
	}

	//Find destination gate
	if (teleport) {
		destination_address = stargates[i]->get_destination();

		i = 0;
		while (destination_gate == nullptr && i < stargates.size()) {
			if (stargates[i]->get_address() == destination_address) {
				destination_gate = stargates[i];
			}
			i++;
		}
	}

	return destination_gate;
}

void stargate_handler::update_animations() {
	for (auto &stargate : stargates) {
		stargate->update_animation();
	}
}
