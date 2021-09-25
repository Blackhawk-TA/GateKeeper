//
// Created by daniel on 24.09.21.
//

#include "items.hpp"

Listbox::Item inventory_item::create_item(inventory_item::ITEM_TYPES item_type) {
	Listbox::Item item;

	switch (item_type) {
		case ITEM_TYPES::GATE_PART:
			item = create_gate_part();
			break;
		case ITEM_TYPES::EXIT:
			item = create_exit();
			break;
		case ITEM_TYPES::COUNTER: //Do nothing, this is the item counter
			break;
	}

	return item;
}

