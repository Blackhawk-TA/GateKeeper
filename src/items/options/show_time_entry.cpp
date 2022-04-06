//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../utils/saves/options.hpp"

Listbox::Item items::create_show_time_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"SHOW TIME",
		"Press A to toggle the game time indicator.",
		"Toggled game time indicator.",
		"",
		false,
		0,
		[] {
			options::show_time = !options::show_time;
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
