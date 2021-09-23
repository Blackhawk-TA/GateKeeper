//
// Created by daniel on 23.09.21.
//

#include <iostream>
#include "inventory.hpp"
#include "sidemenu.hpp"

void inventory::init() {
	control = nullptr;
	items = {
		Listbox::Item{ //TODO maybe add callback_failed_tooltip
			"GATE PART",
			"Can be used to repair a broken stargate.",
			"The stargate was repaired!",
			[] {
				std::cout << "Repair gate" << std::endl;
			}
		},
		Listbox::Item{
			"EXIT",
			"Press A to go back to the menu.",
			"",
			[] {
				inventory::close();
				sidemenu::open();
			}
		}
	};
}

void inventory::add_item(Listbox::Item &item) {
	items.push_back(item);
}

bool inventory::remove_item() {
	return false;
}

void inventory::open() {
	control = new Listbox(Rect(15, 0, 5, 6), items);
}

void inventory::close() {
	delete control;
	control = nullptr;
}

bool inventory::is_open() {
	return control != nullptr;
}

void inventory::draw() {
	control->draw();
}

void inventory::cursor_up() {
	control->cursor_up();
}

void inventory::cursor_down() {
	control->cursor_down();
}

void inventory::cursor_press() {
	control->cursor_press();
}
