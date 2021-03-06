//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

Listbox::Item items::create_gear_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"GEAR",
		"Press A to show your gear, press B to return to menu.",
		"",
		"",
		false,
		0,
		[] {
			game::sidemenu::open(game::sidemenu::GEAR);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
