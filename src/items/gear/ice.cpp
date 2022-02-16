//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item items::create_gear_ice(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"BLUE STONE",
		"The blue stone allows you to control the water during a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
