//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/inventory.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

Listbox::Item listbox_item::create_exit_entry() {
	return Listbox::Item{
		"BACK",
		"Press A to go back.",
		"",
		"",
		false,
		0,
		[] {
			if (inventory::is_open()) {
				inventory::close();
				sidemenu::open();
			} else if (sidemenu::is_open()) {
				sidemenu::close();
			}
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
