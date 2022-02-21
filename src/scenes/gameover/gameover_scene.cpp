//
// Created by daniel on 06.01.22.
//

#include <iostream>
#include "gameover_scene.hpp"
#include "../../game.hpp"
#include "../../utils/saves/savegame.hpp"

namespace gameover {
	Scene::Scene(const SceneOptions& options) {
		Scene::save_id = options.save_id;
		last_buttons = 0;
		changed = 0;
		textbox = new Textbox("You became unconscious. You wake up at the hospital.");
		bool save_converted = savegame::convert_tmp_save(save_id);
		if (!save_converted) {
			std::cerr << "Could not convert temporary save to normal save" << std::endl; //This should never happen
		}
	}

	Scene::~Scene() {
		delete textbox;
		textbox = nullptr;
	}

	void Scene::render(uint32_t time) {
		screen.pen = Pen(0, 0, 0, 255);
		screen.rectangle(Rect(0, 0, 320, 240));

		if (textbox != nullptr) {
			textbox->draw();
		}
	}

	void Scene::update(uint32_t time) {}

	void Scene::inputs() {
		changed = buttons ^ last_buttons;

		if (buttons & changed & Button::A) {
			SceneOptions options = {
				save_id,
				CombatData{},
				GameData{
					Signature{},
					0,
					false,
				},
				true
			};
			load_scene(GAME, options);
		}

		last_buttons = buttons;
	}
}
