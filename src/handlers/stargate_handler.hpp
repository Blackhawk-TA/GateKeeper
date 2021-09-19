//
// Created by daniel on 18.09.21.
//

#pragma once
#include "../utils/utils.hpp"

namespace stargate_handler {
	void init();
	bool check_collisions(Point next_position);
	void check_activations(Point next_position);
	void check_enter(Point next_position);
	void draw_stargates();
	void update_animations();

	enum Stargates {
		GRASSLAND = 1
	};
}
