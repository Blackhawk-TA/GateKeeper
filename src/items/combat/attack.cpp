//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item listbox_item::create_combat_attack(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"ATTACK",
		"Simple attack using not much stamina.",
		"You hit your enemy!",
		"Attack missed.",
		false,
		0,
		[] {
			if (blit::random() % 5 == 0) {
				return Listbox::Tooltip::FAILURE;
			} else {
				return Listbox::Tooltip::SUCCESS;
			}
		}
	};
}
