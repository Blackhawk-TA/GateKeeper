//
// Created by daniel on 24.09.21.
//

#include "items.hpp"
#include "../game.hpp"

Listbox::Item listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM item_type) {
	Listbox::Item item;

	switch (item_type) {
		case INVENTORY_ITEM::GATE_PART:
			item = create_gate_part();
			break;
		case INVENTORY_ITEM::EXIT_INVENTORY:
			item = create_exit_entry();
			break;
	}

	return item;
}

Listbox::Item listbox_item::create_sidemenu_item(listbox_item::SIDEMENU_ITEM item_type, uint8_t save_id) {
	Listbox::Item item;

	switch (item_type) {
		case SIDEMENU_ITEM::INVENTORY:
			item = create_inventory_entry();
			break;
		case SIDEMENU_ITEM::SHOW_FPS:
			item = create_show_fps_entry();
			break;
		case SIDEMENU_ITEM::SAVE:
			item = create_save_entry(save_id);
			break;
		case SIDEMENU_ITEM::EXIT:
			item = create_exit_entry();
			break;
	}

	return item;
}

Listbox::Item listbox_item::create_menu_item(listbox_item::MENU_ITEM item_type, uint8_t save_id) {
	std::string save_id_str = std::to_string(save_id);

	Listbox::Item item;

	switch (item_type) {
		case MENU_ITEM::LOAD_SAVE:
			item = create_load_entry(save_id);
			break;
		case MENU_ITEM::NEW_SAVE:
			item = create_new_save_entry(save_id);
			break;
		case MENU_ITEM::SETTINGS:
			break;
	}

	return item;
}
