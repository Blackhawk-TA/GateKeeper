//
// Created by daniel on 25.12.21.
//

#include <iostream>
#include "combat_scene.hpp"
#include "../../engine/camera.hpp"
#include "ui/combat_menu.hpp"
#include "ui/combat_stats.hpp"
#include "handlers/character_handler.hpp"

namespace combat {
	//TODO use TMP_SAVE_ID when returning to game_scene
	Scene::Scene(CombatData combat_data) {
		map_section = combat_data.map_section;
		load_combat_scene();

		character_handler::init(combat_data);
		menu::init(TMP_SAVE_ID);
		menu::open();
	}

	Scene::~Scene() {
		character_handler::cleanup();
	};

	void Scene::render(uint32_t time) {
		map::draw();
		character_handler::draw();
		menu::draw();
		stats::draw(90, 100, 10);
	}

	void Scene::update(uint32_t time) {
		character_handler::update(time);
	}

	void Scene::inputs() {
		changed = buttons ^ last_buttons;

		if (buttons & changed & Button::DPAD_UP) {
			menu::cursor_up();
		} else if (buttons & changed & Button::DPAD_DOWN) {
			menu::cursor_down();
		} else if (buttons & changed & Button::A) {
			menu::cursor_press();
		}

		last_buttons = buttons;
	}

	void Scene::load_combat_scene() {
		switch (map_section) {
			case map::GRASSLAND: //TODO remove this line
			case map::DUNGEON:
				map::load_section(map::DUNGEON_COMBAT);
				break;
			default:
				std::cerr << "No matching combat area for map section found" << std::endl;
				exit(1);
		}
		camera::set_position(Point(15, 12));
	}
}