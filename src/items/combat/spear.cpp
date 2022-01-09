//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item listbox_item::create_combat_attack_spear(uint8_t type_id, combat::Player *player, combat::Enemy *enemy) {
	return Listbox::Item{
		type_id,
		"SPEAR",
		"Throws a spear at the enemy. Uses more stamina than sword but also does more damage.",
		"Attacking!",
		"Not enough stamina for this attack",
		false,
		0,
		[player, enemy] {
			if (combat::character_handler::attack(AttackType::SPEAR, player, enemy)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
