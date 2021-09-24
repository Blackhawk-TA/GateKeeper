//
// Created by daniel on 23.09.21.
//

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
			1,
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
			0,
			[] {
				inventory::close();
				sidemenu::open();
				return Listbox::Tooltip::SUPPRESS;
			}
		}
	};
}

bool inventory::add_item(Listbox::Item item) {
	return control->add_item(item);
}

void inventory::open() {
	control = new Listbox(Rect(14, 0, 6, 6), items);
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
