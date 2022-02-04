//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/game_objects/handler/game_object_handler.hpp"

Listbox::Item listbox_item::create_gate_part(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"GATE PART",
		"Can be used to repair a broken stargate.",
		"The gate part was used to repair the stargate.",
		"Cannot repair stargate here. It has to be broken and you have to stand directly in front of it.",
		true,
		1,
		[] {
			if (game::game_objects::inventory_interact(listbox_item::GATE_PART)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
