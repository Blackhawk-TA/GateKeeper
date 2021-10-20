//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

//TODO save options in struct, this is not done currently
// move options saving from MenuScene to own namespace in utils
Listbox::Item listbox_item::create_options_exit_entry(uint8_t save_id) {
	return Listbox::Item{
		"EXIT",
		"Press A to go to close options.",
		"",
		"",
		false,
		0,
		[save_id] {
			load_previous_scene(save_id);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
