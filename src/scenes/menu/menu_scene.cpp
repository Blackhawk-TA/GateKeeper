//
// Created by daniel on 17.10.21.
//

#include "menu_scene.hpp"
#include "../../game.hpp"
#include "../../items/items.hpp"
#include "../../utils/saves/options.hpp"

namespace menu {
	Scene::Scene() {
		last_buttons = 0;
		changed = 0;

		options::load();
		create_list_entries();

		listbox = new Listbox(Rect(15, 0, 5, 6), saves, false);
	}

	Scene::~Scene() {
		delete listbox;
		listbox = nullptr;
	}

	void Scene::create_list_entries() {
		for (uint8_t i = 0u; i < options::save_count; i++) {
			saves.emplace_back(items::create_menu_item(items::MENU_ITEM::LOAD_SAVE, i + 1));
		}

		if (options::save_count < options::MAX_SAVES) {
			saves.emplace_back(items::create_menu_item(items::MENU_ITEM::NEW_SAVE, options::save_count + 1));
		}

		saves.emplace_back(items::create_menu_item(items::MENU_ITEM::MENU_OPTIONS));
	}

	void Scene::render(uint32_t time) {
		screen.pen = Pen(0, 0, 0, 255);
		screen.rectangle(Rect(0, 0, 320, 240));

		listbox->draw();
	}

	void Scene::update(uint32_t time) {
	}

	void Scene::inputs() {
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
}
