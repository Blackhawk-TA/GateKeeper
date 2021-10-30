//
// Created by daniel on 23.09.21.
//

#include "inventory.hpp"
#include "../items/items.hpp"

Listbox *control;

void inventory::init() {
	open = false;
	std::vector<Listbox::Item> items = {
		listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::INVENTORY_BACK)
	};
	control = new Listbox(Rect(14, 0, 6, 7), items);
}

/**
 * Load a inventory that was stored in the save game
 * @param loaded_items The stored items from the save game
 */
void inventory::load(std::vector<Listbox::Item> loaded_items) {
	control->set_items(loaded_items);
}

void inventory::cleanup() {
	open = false;
	delete control;
}

bool inventory::add_item(Listbox::Item item) {
	return control->add_item(item);
}

std::vector<Listbox::Item> inventory::get_items() {
	return control->get_items();
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
