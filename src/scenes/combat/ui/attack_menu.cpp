//
// Created by daniel on 26.12.21.
//

#include "attack_menu.hpp"
#include "../../../items/items.hpp"

namespace combat {
	void attack_menu::init(uint8_t save_id, Player *player, Enemy *enemy) {
		control = nullptr;
		items = {
			listbox_item::create_combat_item(listbox_item::COMBAT_ITEM::ATTACK, save_id, player, enemy),
			listbox_item::create_combat_item(listbox_item::COMBAT_ITEM::ESCAPE, save_id),
		};
	}

	void attack_menu::open() {
		control = new Listbox(Rect(16, 0, 4, 7), items);
	}

	void attack_menu::close() { //TODO close menu when attack is selected
		delete control;
		control = nullptr;
	}

	bool attack_menu::is_open() {
		return control != nullptr;
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
		control->cursor_press();
	}
}
