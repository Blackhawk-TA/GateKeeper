//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../utils/saves/options.hpp"

Listbox::Item listbox_item::create_options_exit_entry(uint8_t type_id, uint8_t save_id) {
	return Listbox::Item{
		type_id,
		"BACK",
		"Press A to go to close options.",
		"",
		"",
		false,
		0,
		[save_id] {
			options::save();
			load_previous_scene(save_id);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
