//
// Created by daniel on 24.09.21.
//

#include "../items.hpp"
#include "../../scenes/game/handlers/game_objects.hpp"

Listbox::Item listbox_item::create_gate_part() {
	return Listbox::Item{
		"GATE PART",
		"Can be used to repair a broken stargate.",
		"The gate part was used to repair the stargate.",
		"Cannot repair stargate here. It has to be broken and you have to stand directly in front of it.",
		true,
		1,
		[] {
			if (game_objects::interact()) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
