//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

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
			if (player->use_stamina(5)) {
				if (blit::random() % 5 == 0) {
					return Listbox::Tooltip::FAILURE;
				} else {
					uint8_t bonus_damage = blit::random() % 10;
					enemy->take_damage(10 + bonus_damage);
					return Listbox::Tooltip::SUCCESS;
				}
			} else {
				return Listbox::Tooltip::FAILURE; //TODO warn because of no stamina
			}
		}
	};
}
