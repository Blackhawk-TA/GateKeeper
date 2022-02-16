//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item items::create_gear_arrow(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"ARROW",
		"Allows you to shoot arrows in a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
