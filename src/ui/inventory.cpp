//
// Created by daniel on 23.09.21.
//

#include <iostream>
#include "inventory.hpp"
#include "sidemenu.hpp"
#include "../handlers/stargate_handler.hpp"

void inventory::init() {
	control = nullptr;
	items = {
		Listbox::Item{
			"GATE PART",
			"Can be used to repair a broken stargate.",
			"The gate part was used to repair the stargate.",
			"Cannot repair stargate. It has to be broken and you have to stand directly in front of it.",
			true,
			[] {
				if (stargate_handler::player_repair_gate()) {
					return Listbox::Tooltip::SUCCESS;
				} else {
					return Listbox::Tooltip::FAILURE;
				}
			}
		},
		Listbox::Item{
			"EXIT",
			"Press A to go back to the menu.",
			"",
			"",
			false,
			[] {
				inventory::close();
				sidemenu::open();
				return Listbox::Tooltip::SUPPRESS;
			}
		}
	};
}

void inventory::add_item(Listbox::Item &item) {
	items.push_back(item);
}

void inventory::remove_item(uint8_t index) {
	auto it = items.begin();
	bool found = false;
	uint8_t counter = 0;

	while (!found && it != items.end()) {
		if (counter == index) {
			it = items.erase(it);
			control->update_list(items);
			found = true;
		} else {
			it++;
			counter++;
		}
	}
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
	uint8_t item_index = control->cursor_press();

	//Delete items that can only be used once
	if (!items.empty() && items[item_index].single_use) {
		remove_item(item_index);
	}
}
