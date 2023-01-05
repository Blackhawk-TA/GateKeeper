//
// Created by daniel on 18.09.21.
//

#include "stargate_handler.hpp"
#include "../game_object_handler.hpp"

namespace game {
	std::vector<Stargate *> stargates = {};

	void stargate_handler::init() {
		std::vector<GameObject *> game_object_collection = game_objects::get_collection();

		for (GameObject *game_object: game_object_collection) {
			if (game_object->get_type() == GameObject::StargateType) {
				stargates.push_back((Stargate *) game_object);
			}
		}
	}

	void stargate_handler::delete_stargate(Signature &signature) {
		auto itr = stargates.begin();

		while (itr != stargates.end()) {
			if (game_objects::has_equal_signature((*itr)->get_signature(), signature)) {
				stargates.erase(itr);
				break;
			} else {
				itr++;
			}
		}
	}

	void stargate_handler::cleanup() {
		//Pointers don't have to be deleted here since this is done in game_objects cleanup
		stargates.clear();
	}

	void stargate_handler::damage_stargate(Signature &signature) {
		auto itr = stargates.begin();

		while (itr != stargates.end()) {
			if (game_objects::has_equal_signature((*itr)->get_signature(), signature)) {
				(*itr)->set_inventory_usable(true);
				break;
			} else {
				itr++;
			}
		}
	}

	Stargate *stargate_handler::get_destination_gate(Point next_position) {
		bool teleport = false;
		StargateAddress destination_address;
		Stargate *destination_gate = nullptr;
		uint8_t i = 0;

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
}
