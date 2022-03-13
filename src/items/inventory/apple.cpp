//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/game_objects/handler/player_handler.hpp"

Listbox::Item items::create_apple(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"Apple",
		"Regenerates 70 health when eaten.",
		"You ate an apple.",
		"You're not hungry.",
		true,
		1,
		[] {
			if (game::player_handler::get_health() < 100) {
				game::player_handler::heal(70);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
