//
// Created by daniel on 26.12.21.
//

#include <iostream>
#include "attack_menu.hpp"
#include "../../../items/items.hpp"

namespace combat {
	Listbox *control;
	bool open_state = false;

	void attack_menu::init(uint8_t save_id, Player *player, Enemy *enemy) {
		std::vector<Listbox::Item> items = {};
		control = new Listbox(Rect(16, 0, 4, 8), items, false);

		std::map<AttackType, listbox_item::COMBAT_ITEM> supported_attacks = {
			{MELEE,  listbox_item::COMBAT_ITEM::ATTACK_SWORD},
			{SPEAR,  listbox_item::COMBAT_ITEM::ATTACK_SPEAR},
			{ARROW,  listbox_item::COMBAT_ITEM::ATTACK_ARROW},
			{DAGGER, listbox_item::COMBAT_ITEM::ATTACK_DAGGER},
			{MAGIC,  listbox_item::COMBAT_ITEM::ATTACK_MAGIC}
		};

		for (auto &attack : player->get_stats().attacks) {
			if (supported_attacks.find(attack) != supported_attacks.end()) {
				add_item(listbox_item::create_combat_item(supported_attacks.at(attack), save_id, player, enemy));
			} else {
				std::cerr << "Unsupported attack for player" << std::endl;
			}
		}

		add_item(listbox_item::create_combat_item(listbox_item::COMBAT_ITEM::ESCAPE, save_id));
	}

	void attack_menu::cleanup() {
		delete control;
		control = nullptr;
	}

	void attack_menu::open() {
		control->set_view_mode(false);
		control->cursor_reset();
		open_state = true;
	}

	void attack_menu::close() {
		open_state = false;
	}

	bool attack_menu::is_open() {
		return open_state;
	}

	bool attack_menu::add_item(Listbox::Item item) {
		return control->add_item(item);
	}

	void attack_menu::draw() {
		control->draw();
	}

	void attack_menu::cursor_up() {
		control->cursor_up();
	}

	void attack_menu::cursor_down() {
		control->cursor_down();
	}

	void attack_menu::cursor_press() {
		control->cursor_press(true);
	}
}
