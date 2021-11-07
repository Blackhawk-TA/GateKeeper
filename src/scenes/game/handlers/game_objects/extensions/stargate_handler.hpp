//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../../../../../utils/utils.hpp"
#include "../../../game_objects/stargate.hpp"

namespace stargate_handler {
	void init();
	void cleanup();
	Stargate *get_destination_gate(Point next_position);
	bool player_repair_gate();
}
