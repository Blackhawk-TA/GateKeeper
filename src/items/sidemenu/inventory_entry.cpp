//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

Listbox::Item items::create_inventory_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"ITEMS",
		"Press A to show items, press B to return to menu.",
		"",
		"",
		false,
		0,
		[] {
			game::sidemenu::open(game::sidemenu::INVENTORY);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
