//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../ui/controls/listbox.hpp"
#include "../handlers/stargate_handler.hpp"

namespace inventory_item {
	const Listbox::Item gate_part = Listbox::Item{
		"GATE PART",
		"Can be used to repair a broken stargate.",
		"The gate part was used to repair the stargate.",
		"Cannot repair stargate. It has to be broken and you have to stand directly in front of it.",
		true,
		1,
		[] {
			if (stargate_handler::player_repair_gate()) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
