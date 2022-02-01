//
// Created by D069765 on 20.10.2021.
//

#include "options_scene.hpp"
#include "../../items/items.hpp"

namespace options {
	Scene::Scene(const SceneOptions& options) {
		Scene::save_id = options.save_id;
		last_buttons = 0;
		changed = 0;
		option_items = {
			listbox_item::create_options_item(listbox_item::OPTIONS_ITEM::SHOW_FPS),
		};

		//Only show reset all option from MENU scene
		if (get_previous_scene() == SceneType::MENU) {
			option_items.emplace_back(listbox_item::create_options_item(listbox_item::OPTIONS_ITEM::RESET_ALL));
		}

		option_items.emplace_back(listbox_item::create_options_item(listbox_item::OPTIONS_ITEM::OPTIONS_BACK, save_id));
		listbox = new Listbox(Rect(15, 0, 5, 6), option_items, false);
	}

	Scene::~Scene() {
		delete listbox;
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
		} else if (buttons & changed & Button::B) {
			load_previous_scene(save_id);
		}

		last_buttons = buttons;
	}
}
