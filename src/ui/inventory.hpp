//
// Created by daniel on 23.09.21.
//

#pragma once

#include "controls/listbox.hpp"

namespace inventory {
	inline Listbox *control;
	inline std::vector<Listbox::Item> items;

	void init();
	void add_item(Listbox::Item &item);
	void open();
	void close();
	bool is_open();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
