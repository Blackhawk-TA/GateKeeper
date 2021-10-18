//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

Listbox::Item listbox_item::create_load_entry(uint8_t save_id) {
	std::string save_id_str = std::to_string(save_id);

	return Listbox::Item{
		"SAVE " + save_id_str,
		"Press A to load save. Press B to delete save.",
		"Loading save...",
		"",
		false,
		0,
		[save_id] {
			load_game_scene(save_id);
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
