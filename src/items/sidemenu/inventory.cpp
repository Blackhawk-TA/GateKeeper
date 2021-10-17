//
// Created by daniel on 26.09.21.
//

#include "../../ui/inventory.hpp"
	 #include "../../ui/sidemenu.hpp"
	 #include "../items.hpp"

Listbox::Item listbox_item::create_inventory_entry() {
	return Listbox::Item{
		"ITEMS",
		"Press A to show items, press B to return to menu.",
		"",
		"",
		false,
		0,
		[] {
			inventory::open();
			sidemenu::close();
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
