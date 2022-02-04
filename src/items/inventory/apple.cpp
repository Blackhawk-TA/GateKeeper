//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/game_objects/player.hpp"

Listbox::Item listbox_item::create_apple(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"Apple",
		"Regenerates 20 health when eaten.",
		"You ate an apple.",
		"You're not hungry.",
		true,
		1,
		[] {
			if (game::Player::get_health() < 100) {
				game::Player::heal(20);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
