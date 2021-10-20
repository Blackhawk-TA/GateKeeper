//
// Created by D069765 on 20.10.2021.
//

#include "options_scene.hpp"
#include "../items/items.hpp"

OptionsScene::OptionsScene() {
	last_buttons = 0;
	changed = 0;
	option_items = {
		listbox_item::create_options_item(listbox_item::OPTIONS_ITEM::SHOW_FPS),
		listbox_item::create_options_item(listbox_item::OPTIONS_ITEM::EXIT_OPTIONS)
	};
	listbox = new Listbox(Rect(0, 0 , 5, 6), option_items, false);
}

OptionsScene::~OptionsScene() {
	delete listbox;
}

void OptionsScene::render(uint32_t time) {
	screen.pen = Pen(0, 0, 0, 255);
	screen.rectangle(Rect(0, 0, 320, 240));

	listbox->draw();
}

void OptionsScene::update(uint32_t time) {
	//Handle button inputs
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::DPAD_UP) {
		listbox->cursor_up();
	} else if (buttons & changed & Button::DPAD_DOWN) {
		listbox->cursor_down();
	} else if (buttons & changed & Button::A) {
		listbox->cursor_press();
	}

	last_buttons = buttons;
}
