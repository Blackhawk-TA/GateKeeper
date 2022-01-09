//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item listbox_item::create_combat_attack_sword(uint8_t type_id, combat::Player *player, combat::Enemy *enemy) {
	return Listbox::Item{
		type_id,
		"SWORD",
		"Simple sword attack. Good balance of stamina use and damage.",
		"Attacking!",
		"Not enough stamina for this attack",
		false,
		0,
		[player, enemy] {
			if (combat::character_handler::attack(AttackType::SWORD, player, enemy)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
