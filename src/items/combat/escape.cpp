//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item items::create_combat_escape(uint8_t type_id, uint8_t save_id) {
	return Listbox::Item{
		type_id,
		"ESCAPE",
		"Tries to escape from the fight.",
		"Escaped!",
		"Could not escape!",
		false,
		0,
		[save_id] {
			//TODO when escaping in front of gate, it doesnt know where to put the player.
			// Add parameter so in this case the player either can't escape or goes back through the gate
			if (combat::character_handler::escape()) {
				combat::character_handler::load_game_scene(save_id, false, false);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		},
		false,
		true,
	};
}
