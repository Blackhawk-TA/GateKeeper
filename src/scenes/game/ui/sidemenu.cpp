//
// Created by daniel on 21.09.21.
//

#include "sidemenu.hpp"
#include "overlay.hpp"
#include "../../../utils/saves/savegame.hpp"

namespace game::sidemenu {
	Listbox *control;
	bool open_state = false;

	void init(uint8_t save_id) {
		std::vector<Listbox::Item> items = {
			listbox_item::create_sidemenu_item(listbox_item::INVENTORY),
			listbox_item::create_sidemenu_item(listbox_item::SIDEMENU_OPTIONS, save_id),
			listbox_item::create_sidemenu_item(listbox_item::SAVE, save_id),
			listbox_item::create_sidemenu_item(listbox_item::SIDEMENU_BACK),
			listbox_item::create_sidemenu_item(listbox_item::QUIT)
		};

		control = new Listbox(Rect(16, 0, 4, 7), items);
	}

	void cleanup() {
		open_state = false;
		delete control;
	}

	void open() {
		open_state = true;
	}

	void close() {
		open_state = false;
		control->cursor_reset();
	}

	bool is_open() {
		return open_state;
	}

	void draw() {
		control->draw();
	}

	void cursor_up() {
		control->cursor_up();
	}

	void cursor_down() {
		control->cursor_down();
	}

	void cursor_press() {
		control->cursor_press();
	}
}