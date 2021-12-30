//
// Created by daniel on 26.12.21.
//

#include "combat_menu.hpp"
#include "../../../items/items.hpp"

namespace combat {
	void menu::init(uint8_t save_id) {
		control = nullptr;
		items = {
			listbox_item::create_combat_item(listbox_item::COMBAT_ITEM::ESCAPE, save_id),
		};
	}

	void menu::open() {
		control = new Listbox(Rect(16, 0, 4, 7), items);
	}

	void menu::close() { //TODO close menu when attack is selected
		delete control;
		control = nullptr;
	}

	bool menu::is_open() {
		return control != nullptr;
	}

	void menu::draw() {
		control->draw();
	}

	void menu::cursor_up() {
		control->cursor_up();
	}

	void menu::cursor_down() {
		control->cursor_down();
	}

	void menu::cursor_press() {
		control->cursor_press();
	}
}
