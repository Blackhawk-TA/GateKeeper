//
// Created by daniel on 17.10.21.
//

#include "menu_scene.hpp"
#include "game.hpp"
#include "items/items.hpp"

MenuScene::MenuScene() {
	last_buttons = 0;
	changed = 0;
	saves = { //TODO save which saves are already in use
		listbox_item::create_menu_item(0)
	};
	listbox = new Listbox(Rect(0, 0, 4, 6), saves);
	textbox = new Textbox();
}

MenuScene::~MenuScene() {
	delete textbox;
	delete listbox;
	textbox = nullptr;
	listbox = nullptr;
}

void MenuScene::render(uint32_t time) {
	screen.pen = Pen(0, 0, 0, 255);
	screen.rectangle(Rect(0, 0, 320, 240));

	textbox->draw();
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
}
