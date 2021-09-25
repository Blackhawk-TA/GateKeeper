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
	//TODO split in menu and inventory items
	enum ITEM_TYPES {
		GATE_PART = 0,
		EXIT = 1,
		COUNTER = 2
	};

	Listbox::Item create_item(ITEM_TYPES item_type);
	Listbox::Item create_gate_part();
	Listbox::Item create_exit();
}
