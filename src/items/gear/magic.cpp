//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item listbox_item::create_gear_magic(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"PURPLE CRYSTAL",
		"The purple crystal gives you magic powers during a fight.",
		"",
		"",
		false,
		0,
		[] {
			return Listbox::Tooltip::SUPPRESS;
		},
	};
}
