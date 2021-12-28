//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/handlers/game_objects/extensions/stargate_handler.hpp"
#include "../../scenes/game/player.hpp"

Listbox::Item listbox_item::create_carrot(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"Carrot",
		"Regenerates 15 health when eaten.",
		"You ate a carrot.",
		"You're not hungry.",
		true,
		1,
		[] {
			if (game::Player::get_health() < 100) {
				game::Player::heal(15);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
