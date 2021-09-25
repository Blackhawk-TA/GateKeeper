//
// Created by daniel on 23.09.21.
//

#pragma once
#include "controls/listbox.hpp"

namespace inventory {
	inline Listbox *control;
	inline std::vector<Listbox::Item> items;

	void init();
	void load(std::vector<Listbox::Item> loaded_items);
	bool add_item(Listbox::Item item);
	std::vector<Listbox::Item> get_items();
	void open();
	void close();
	bool is_open();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
