//
// Created by daniel on 17.10.21.
//

#include "menu_scene.hpp"
#include "../game.hpp"
#include "../items/items.hpp"

MenuScene::MenuScene() {
	last_buttons = 0;
	changed = 0;
	saves_count = 0,
	show_fps = false;

	load_menu_data();
	create_list_entries();

	listbox = new Listbox(Rect(0, 0, 5, 6), saves, false);
}

MenuScene::~MenuScene() {
	save_menu_data();
	delete listbox;
	listbox = nullptr;
}

void MenuScene::create_list_entries() {
	for (uint8_t i = 0u; i < saves_count; i++) {
		saves.emplace_back(listbox_item::create_menu_item(listbox_item::MENU_ITEM::LOAD_SAVE, i + 1));
	}

	if (saves_count < MAX_SAVES) {
		saves.emplace_back(listbox_item::create_menu_item(listbox_item::MENU_ITEM::NEW_SAVE, saves_count + 1));
	}

	saves.emplace_back(listbox_item::create_menu_item(listbox_item::MENU_ITEM::MENU_OPTIONS));
}

void MenuScene::render(uint32_t time) {
	screen.pen = Pen(0, 0, 0, 255);
	screen.rectangle(Rect(0, 0, 320, 240));

	listbox->draw();
}

void MenuScene::update(uint32_t time) {
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

void MenuScene::save_menu_data() {
	MenuData menu_data = {
		saves_count,
		show_fps
	};

	write_save(menu_data, MENU_DATA_SLOT);
}

void MenuScene::load_menu_data() {
	MenuData menu_data{};
	bool save_found = read_save(menu_data, MENU_DATA_SLOT);

	if (save_found) {
		saves_count = menu_data.save_count;
		show_fps = menu_data.show_fps;
	}
}
