//
// Created by D069765 on 20.10.2021.
//

#include "settings_scene.hpp"
#include "../items/items.hpp"

SettingsScene::SettingsScene() {
	last_buttons = 0;
	changed = 0;
	settings_items = {
		listbox_item::create_settings_item(listbox_item::SETTINGS_ITEM::SHOW_FPS),
		listbox_item::create_settings_item(listbox_item::SETTINGS_ITEM::EXIT_SETTINGS)
	};
	listbox = new Listbox(Rect(0, 0 , 5, 6), settings_items, false);
}

SettingsScene::~SettingsScene() {
	delete listbox;
}

void SettingsScene::render(uint32_t time) {
	screen.pen = Pen(0, 0, 0, 255);
	screen.rectangle(Rect(0, 0, 320, 240));

	listbox->draw();
}

void SettingsScene::update(uint32_t time) {
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
