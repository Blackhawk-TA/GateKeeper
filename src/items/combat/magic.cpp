//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"
#include "../../scenes/combat/handlers/character_handler.hpp"

Listbox::Item items::create_combat_attack_magic(uint8_t type_id, combat::Player *player, combat::Enemy *enemy) {
	return Listbox::Item{
		type_id,
		"MAGIC",
		"Magic powers deal damage! High stamina usage and damage.",
		"Attacking!",
		"Not enough stamina for this attack",
		false,
		0,
		[player, enemy] {
			if (combat::character_handler::attack(GEAR_MAGIC, player, enemy)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
