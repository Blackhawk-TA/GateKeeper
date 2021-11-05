//
// Created by daniel on 23.09.21.
//

#pragma once

#include "../../../engine/ui/listbox.hpp"

namespace inventory {
	void init();
	void load(std::vector<Listbox::Item> loaded_items);
	void cleanup();
	void open();
	void close();
	bool is_open();
	bool add_item(Listbox::Item item);
	std::vector<Listbox::Item> get_items();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
