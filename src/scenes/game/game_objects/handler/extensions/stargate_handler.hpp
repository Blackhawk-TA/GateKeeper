//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../../objects/stargate.hpp"

namespace game::stargate_handler {
	void init();
	void delete_stargate(Signature &signature);
	void cleanup();

	/**
	 * Sets the state of a stargate to broken
	 * @param signature The signature of the stargate
	 */
	void damage_stargate(Signature &signature);

	/**
	 * Checks if the players next position triggers a teleportation and returns the destination gate, if existing
	 * @param next_position The next position of the player
	 * @return The position of the destination gate if there is one, else Point(0, 0) is returned
	 */
	Stargate *get_destination_gate(Point next_position);
}
