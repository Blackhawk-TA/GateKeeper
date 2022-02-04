//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../../objects/stargate.hpp"

namespace game::stargate_handler {
	void init();
	void delete_stargate(Signature &signature);
	void cleanup();
	Stargate *get_destination_gate(Point next_position);
}