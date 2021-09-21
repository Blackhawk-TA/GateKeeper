//
// Created by daniel on 21.09.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "box.hpp"

namespace sidemenu {
	void init();
	void draw();
	void cursor_up();
	void cursor_down();
	void press();
	extern bool visible;
}