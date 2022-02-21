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
		control = new Listbox(Rect(16, 0, 4, 8), items);

		std::map<GEAR_TYPE, items::COMBAT_ITEM> supported_attacks = {
			{GEAR_SWORD,  items::COMBAT_ITEM::ATTACK_SWORD},
			{GEAR_SPEAR,  items::COMBAT_ITEM::ATTACK_SPEAR},
			{GEAR_ARROW,  items::COMBAT_ITEM::ATTACK_ARROW},
			{GEAR_DAGGER, items::COMBAT_ITEM::ATTACK_DAGGER},
			{GEAR_MAGIC,  items::COMBAT_ITEM::ATTACK_MAGIC},
			{GEAR_FIRE,   items::COMBAT_ITEM::ATTACK_FIRE},
			{GEAR_ICE,    items::COMBAT_ITEM::ATTACK_ICE},
			{GEAR_SHOCK,  items::COMBAT_ITEM::ATTACK_SHOCK},
		};

		for (auto &attack : player->get_stats().attacks) {
			if (supported_attacks.find(attack) != supported_attacks.end()) {
				add_item(items::create_combat_item(supported_attacks.at(attack), save_id, player, enemy));
			} else {
				std::cerr << "Unsupported attack for player" << std::endl;
			}
		}

		add_item(items::create_combat_item(items::COMBAT_ITEM::ESCAPE, save_id));
	}

	void attack_menu::cleanup() {
		delete control;
		control = nullptr;
	}

	void attack_menu::open() {
		control->set_view_mode(false);
		control->update_tooltip();
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

	void attack_menu::set_view_mode(bool value) {
		control->set_view_mode(value);
	}
}
