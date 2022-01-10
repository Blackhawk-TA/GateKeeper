//
// Created by daniel on 21.09.21.
//

#pragma once

#include "../../../engine/ui/listbox.hpp"

namespace game::sidemenu {
	void init(uint8_t save_id);
	void cleanup();
	void open();
	void close();
	bool is_open();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
