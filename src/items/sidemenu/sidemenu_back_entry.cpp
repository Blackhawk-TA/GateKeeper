//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

Listbox::Item items::create_back_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"BACK",
		"Press A to go back.",
		"",
		"",
		false,
		0,
		[] {
			game::sidemenu::navigate_back();
			return Listbox::Tooltip::SUPPRESS;
		},
		false,
		true,
	};
}
