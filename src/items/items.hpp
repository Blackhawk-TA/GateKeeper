//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../ui/controls/listbox.hpp"
#include "../handlers/stargate_handler.hpp"

/**
 * Contains the create function for all inventory items
 */
namespace listbox_item {
	const uint8_t INVENTORY_COUNTER = 2; //Amount of individual items in inventory
	enum INVENTORY_ITEM {
		GATE_PART = 1,
		EXIT_INVENTORY = 2
	};

	enum SIDEMENU_ITEM {
		INVENTORY = 1,
		SHOW_FPS = 2,
		SAVE = 3,
		EXIT = 4
	};

	enum MENU_ITEM {
		LOAD_SAVE = 1,
		NEW_SAVE = 2,
		SETTINGS = 3
	};

	Listbox::Item create_inventory_item(INVENTORY_ITEM item_type);
	Listbox::Item create_sidemenu_item(SIDEMENU_ITEM item_type, uint8_t save_id = 0);
	Listbox::Item create_menu_item(MENU_ITEM item_type, uint8_t save_id);

	Listbox::Item create_gate_part();

	Listbox::Item create_inventory_entry();
	Listbox::Item create_show_fps_entry();
	Listbox::Item create_save_entry(uint8_t save_id);
	Listbox::Item create_exit_entry();

	Listbox::Item create_load_entry(uint8_t save_id);
	Listbox::Item create_new_save_entry(uint8_t save_id);
}
