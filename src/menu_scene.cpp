//
// Created by daniel on 17.10.21.
//

#include "menu_scene.hpp"
#include "engine/transition.hpp"
#include "game.hpp"

MenuScene::MenuScene() {
	last_buttons = 0;
	changed = 0;
	save_id = 0;
//	listbox = new Listbox(Rect(0, 0, 75, 100), )
	textbox = new Textbox("");
}

MenuScene::~MenuScene() {
	delete textbox;
}

void MenuScene::render(uint32_t time) {
	textbox->draw();
}

void MenuScene::update(uint32_t time) {
	//Handle button inputs
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::A) {
		transition::start(load_game_scene);
	}
}
