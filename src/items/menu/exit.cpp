//
// Created by daniel on 26.09.21.
//

#include "../../ui/inventory.hpp"
#include "../../ui/sidemenu.hpp"
#include "../items.hpp"

Listbox::Item inventory_item::create_exit() {
	return Listbox::Item{
		"EXIT",
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
