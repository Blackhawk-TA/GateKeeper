//
// Created by daniel on 22.08.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

namespace camera {
	void init(Point start_position);
	bool is_moving();
	Point get_world_position();
	Point get_screen_position();
	void set_position(Point position);
	void move(Point &offset);
	void update_position();
}
