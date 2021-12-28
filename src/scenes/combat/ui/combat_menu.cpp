//
// Created by daniel on 26.12.21.
//

#include "combat_menu.hpp"

namespace combat {
	void menu::init() {
		control = nullptr;
		items = {
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
