//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../ui/controls/listbox.hpp"
#include "../handlers/stargate_handler.hpp"

/**
 * Contains the create function for all inventory items
 */
namespace inventory_item {
	enum INVENTORY_ITEM {
		GATE_PART = 0,
		INVENTORY_COUNTER = 2
	};

	enum MENU_ITEM {
		INVENTORY = 0,
		SHOW_FPS = 1,
		SAVE = 2,
		EXIT = 3,
		MENU_COUNTER = 4
	};

	Listbox::Item create_inventory_item(INVENTORY_ITEM item_type);
	Listbox::Item create_menu_item(MENU_ITEM item_type);

	Listbox::Item create_gate_part();
	Listbox::Item create_inventory_entry();
	Listbox::Item create_show_fps_entry();
	Listbox::Item create_save_entry();
	Listbox::Item create_exit_entry();
}
