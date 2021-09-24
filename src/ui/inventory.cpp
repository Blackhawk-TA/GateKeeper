//
// Created by daniel on 23.09.21.
//

#include "inventory.hpp"
#include "sidemenu.hpp"
#include "../handlers/stargate_handler.hpp"
#include "../items/gate_part.hpp"

void inventory::init() {
	control = nullptr;
	items = {
		inventory_item::gate_part,
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
	items = control->get_items(); //Update item list on close
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
