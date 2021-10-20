//
// Created by daniel on 21.09.21.
//

#include "sidemenu.hpp"
#include "overlay.hpp"
#include "../utils/saves/savegame.hpp"

void sidemenu::init(uint8_t save_id) {
	control = nullptr;
	items = {
		listbox_item::create_sidemenu_item(listbox_item::INVENTORY),
		listbox_item::create_sidemenu_item(listbox_item::SIDEMENU_OPTIONS, save_id),
		listbox_item::create_sidemenu_item(listbox_item::SAVE, save_id),
		listbox_item::create_sidemenu_item(listbox_item::EXIT)
	};
}

void sidemenu::open() {
	control = new Listbox(Rect(16, 0, 4, 6), items);
}

void sidemenu::close() {
	delete control;
	control = nullptr;
}

bool sidemenu::is_open() {
	return control != nullptr;
}

void sidemenu::draw() {
	control->draw();
}

void sidemenu::cursor_up() {
	control->cursor_up();
}

void sidemenu::cursor_down() {
	control->cursor_down();
}

void sidemenu::cursor_press() {
	control->cursor_press();
}
