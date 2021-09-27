//
// Created by daniel on 24.09.21.
//

#include "items.hpp"

Listbox::Item inventory_item::create_inventory_item(inventory_item::INVENTORY_ITEM item_type) {
	Listbox::Item item;

	switch (item_type) {
		case INVENTORY_ITEM::GATE_PART:
			item = create_gate_part();
			break;
		case INVENTORY_ITEM::EXIT_INVENTORY:
			item = create_exit_entry();
			break;
		case INVENTORY_ITEM::INVENTORY_COUNTER: //Do nothing, this is the item counter
			break;
	}

	return item;
}

Listbox::Item inventory_item::create_menu_item(inventory_item::MENU_ITEM item_type) {
	Listbox::Item item;

	switch (item_type) {
		case MENU_ITEM::INVENTORY:
			item = create_inventory_entry();
			break;
		case MENU_ITEM::SHOW_FPS:
			item = create_show_fps_entry();
			break;
		case MENU_ITEM::SAVE:
			item = create_save_entry();
			break;
		case MENU_ITEM::EXIT:
			item = create_exit_entry();
			break;
		case MENU_ITEM::MENU_COUNTER: //Do nothing, this is the item counter
			break;
	}

	return item;
}

