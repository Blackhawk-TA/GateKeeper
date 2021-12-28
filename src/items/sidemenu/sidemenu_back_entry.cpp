//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/inventory.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

Listbox::Item listbox_item::create_back_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"BACK",
		"Press A to go back.",
		"",
		"",
		false,
		0,
		[] {
			if (game::inventory::is_open()) {
				game::inventory::close();
				game::sidemenu::open();
			} else if (game::sidemenu::is_open()) {
				game::sidemenu::close();
			}
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
