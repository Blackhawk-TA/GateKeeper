//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item items::create_combat_attack_shock(uint8_t type_id, combat::Player *player, combat::Enemy *enemy) {
	return Listbox::Item{
		type_id,
		"SHOCK",
		"Hits your enemy with an electric shock! High stamina usage and damage.",
		"Attacking!",
		"Not enough stamina for this attack",
		false,
		0,
		[player, enemy] {
			if (combat::character_handler::attack(GEAR_SHOCK, player, enemy)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
