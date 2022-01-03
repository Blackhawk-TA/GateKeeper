//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item listbox_item::create_combat_escape(uint8_t type_id, uint8_t save_id) {
	return Listbox::Item{
		type_id,
		"ESCAPE",
		"Tries to escape from the fight.",
		"Escaped!",
		"Could not escape!",
		false,
		0,
		[save_id] {
			if (combat::character_handler::escape()) {
				combat::character_handler::load_game_scene(save_id, false);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
