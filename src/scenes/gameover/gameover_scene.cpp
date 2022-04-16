//
// Created by daniel on 06.01.22.
//

#include <iostream>
#include "gameover_scene.hpp"
#include "../../game.hpp"

namespace gameover {
	Scene::Scene(const SceneOptions& opts) {
		save_id = opts.save_id;
		respawn = opts.game_data.respawn;
		won_fight = opts.game_data.won_fight;
		last_buttons = 0;
		changed = 0;

		if (won_fight && respawn) { //Game finished by beating the boss and respawning at home
			textbox = new Textbox("You defeated the king and ended his reign of terror. The villagers are now safe again. Thank you for playing.");
		} else {
			textbox = new Textbox("You became unconscious. You wake up at the hospital.");
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
			if (!textbox->next()) {
				SceneOptions options = {
					save_id,
					CombatData{},
					GameData{
						Signature{},
						0,
						won_fight,
						respawn,
					},
				};
				load_scene(SceneType::GAME, options);
			}
		}

		last_buttons = buttons;
	}
}
