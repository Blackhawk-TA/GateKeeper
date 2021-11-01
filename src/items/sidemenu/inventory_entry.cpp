//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/inventory.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

Listbox::Item listbox_item::create_inventory_entry() {
	return Listbox::Item{
		"ITEMS",
		"Press A to show items, press B to return to menu.",
		"",
		"",
		false,
		0,
		[] {
			inventory::open = true;
			sidemenu::close();
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
