//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../../../utils/utils.hpp"
#include "../game_objects/stargate.hpp"

namespace stargate_handler {
	void init();
	Stargate *get_destination_gate(Point next_position);
	void update_animations();
}
