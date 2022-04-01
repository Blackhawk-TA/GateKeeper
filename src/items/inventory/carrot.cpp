//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/game_objects/handler/player_handler.hpp"

Listbox::Item items::create_carrot(uint8_t type_id) {
	uint8_t heal_amount = 75;
	return Listbox::Item{
		type_id,
		"Carrot",
		"Regenerates " + std::to_string(heal_amount) + " health when eaten.",
		"You ate a carrot.",
		"You're not hungry.",
		true,
		1,
		[heal_amount] {
			if (game::player_handler::get_health() < 100) {
				game::player_handler::heal(heal_amount);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
