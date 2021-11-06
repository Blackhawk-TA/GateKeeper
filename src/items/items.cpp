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
		case INVENTORY_ITEM::APPLE:
			item = create_apple();
			break;
		case INVENTORY_ITEM::INVENTORY_BACK:
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
		case SIDEMENU_ITEM::SAVE:
			item = create_save_entry(save_id);
			break;
		case SIDEMENU_ITEM::SIDEMENU_OPTIONS:
			item = create_options_entry(save_id);
			break;
		case SIDEMENU_ITEM::SIDEMENU_BACK:
			item = create_exit_entry();
			break;
		case SIDEMENU_ITEM::QUIT:
			item = create_quit_entry();
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
		case MENU_ITEM::MENU_OPTIONS:
			item = create_options_entry();
			break;
	}

	return item;
}

Listbox::Item listbox_item::create_options_item(listbox_item::OPTIONS_ITEM item_type, uint8_t save_id) {
	Listbox::Item item;

	switch (item_type) {
		case OPTIONS_ITEM::SHOW_FPS:
			item = create_show_fps_entry();
			break;
		case OPTIONS_ITEM::OPTIONS_BACK:
			item = create_options_exit_entry(save_id);
			break;
	}

	return item;
}
