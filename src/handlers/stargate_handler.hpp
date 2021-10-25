//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "../game_objects/stargate.hpp"

namespace stargate_handler {
	void init();
	void load(std::map<StargateAddresses, Stargate> saved_stargates);
	bool check_collisions(Point next_position);
	void update_states(Point next_position);
	Stargate *get_destination_gate(Point next_position);
	void draw_stargates();
	void update_animations();
	bool player_repair_gate();
	std::map<StargateAddresses, Stargate> get_stargates();
}
