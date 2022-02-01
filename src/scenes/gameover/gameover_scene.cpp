//
// Created by daniel on 06.01.22.
//

#include "gameover_scene.hpp"
#include "../../game.hpp"

namespace gameover {
	Scene::Scene(const SceneOptions& options) {
		Scene::save_id = options.save_id;
		last_buttons = 0;
		changed = 0;
		textbox = new Textbox("You became unconscious. You wake up at the hospital.");
	}

	Scene::~Scene() {
		delete textbox;
		textbox = nullptr;
	}

	void Scene::render(uint32_t time) {
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
