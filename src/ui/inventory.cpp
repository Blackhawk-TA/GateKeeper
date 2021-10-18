//
// Created by daniel on 23.09.21.
//

#include "inventory_entry.hpp"
#include <utility>
#include "../items/items.hpp"

void inventory::init() {
	control = nullptr;
	items = {
		listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::GATE_PART),
		listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::EXIT_INVENTORY)
	};
}

/**
 * Load a inventory that was stored in the save game
 * @param loaded_items The stored items from the save game
 */
void inventory::load(std::vector<Listbox::Item> loaded_items) {
	items = std::move(loaded_items);
}

bool inventory::add_item(Listbox::Item item) {
	return control->add_item(item);
}

std::vector<Listbox::Item> inventory::get_items() {
	return items;
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
