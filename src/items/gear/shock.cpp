//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item items::create_gear_shock(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"YELLOW STONE",
		"The yellow stone allows you to control the electric energy during a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
