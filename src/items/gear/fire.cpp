//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item items::create_gear_fire(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"RED STONE",
		"The red stone allows you to control the fire during a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
