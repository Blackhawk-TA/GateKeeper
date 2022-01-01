//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item listbox_item::create_combat_attack(uint8_t type_id, combat::Player *player, combat::Enemy *enemy) {
	return Listbox::Item{
		type_id,
		"ATTACK",
		"Simple attack using not much stamina.",
		"You hit your enemy!",
		"Attack failed.",
		false,
		0,
		[player, enemy] {
			if (combat::character_handler::attack_light(player, enemy)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
