//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item items::create_gear_spear(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"SPEAR",
		"Allows you to throw a spear during a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		},
	};
}
