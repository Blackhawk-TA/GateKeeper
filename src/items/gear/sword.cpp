//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item listbox_item::create_gear_sword(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"SWORD",
		"Allows you to attack your enemy with a sword during a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		},
	};
}
