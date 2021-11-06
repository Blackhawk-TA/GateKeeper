//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/handlers/game_objects/extensions/stargate_handler.hpp"
#include "../../scenes/game/characters/player.hpp"

Listbox::Item listbox_item::create_apple() {
	return Listbox::Item{
		"Apple",
		"Regenerates 20 health when eaten.",
		"You ate an apple.",
		"You're not hungry.",
		true,
		1,
		[] {
			if (Player::get_health() < 100) {
				Player::heal(20);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
