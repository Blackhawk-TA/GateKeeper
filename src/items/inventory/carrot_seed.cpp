//
// Created by daniel on 07.11.21.
//

#include "../items.hpp"
#include "../../scenes/game/handlers/game_objects/game_object_handler.hpp"

Listbox::Item listbox_item::create_carrot_seed(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"Carrot Seed",
		"When planted, it can grow, be harvested and eaten by you.",
		"You planted carrot seeds.",
		"You cannot plant carrot seeds here. Find a carrot bed.",
		true,
		1,
		[] {
			if (game::game_objects::inventory_interact(listbox_item::CARROT_SEED)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
