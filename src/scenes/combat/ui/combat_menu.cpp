//
// Created by daniel on 26.12.21.
//

#include "combat_menu.hpp"

void combat_menu::init() {
	control = nullptr;
	items = {
	};
}

void combat_menu::open() {
	control = new Listbox(Rect(16, 0, 4, 7), items);
}

void combat_menu::close() { //TODO close menu when attack is selected
	delete control;
	control = nullptr;
}

bool combat_menu::is_open() {
	return control != nullptr;
}

void combat_menu::draw() {
	control->draw();
}

void combat_menu::cursor_up() {
	control->cursor_up();
}

void combat_menu::cursor_down() {
	control->cursor_down();
}

void combat_menu::cursor_press() {
	control->cursor_press();
}
