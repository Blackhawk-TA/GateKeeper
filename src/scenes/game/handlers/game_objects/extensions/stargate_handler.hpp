//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../../../game_objects/stargate.hpp"

namespace stargate_handler {
	void init();
	void cleanup();
	Stargate *get_destination_gate(Point next_position);
}
