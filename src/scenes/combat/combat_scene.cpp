//
// Created by daniel on 25.12.21.
//

#include <iostream>
#include "combat_scene.hpp"
#include "../../engine/camera.hpp"
#include "ui/attack_menu.hpp"
#include "ui/stats.hpp"
#include "handlers/character_handler.hpp"

namespace combat {
	Player *player;
	Enemy *enemy;

	Scene::Scene(SceneOptions options) {
		map_section = options.combat_data.map_section;
		load_combat_scene();

		character_handler::init(options.combat_data);
		enemy = character_handler::get_enemy();
		player = character_handler::get_player();

		attack_menu::init(TMP_SAVE_ID);
		attack_menu::open();
	}

	Scene::~Scene() {
		character_handler::cleanup();
	};

	void Scene::render(uint32_t time) {
		map::draw();
		character_handler::draw();
		attack_menu::draw();
		stats::draw(player->get_health(), player->get_stamina(), enemy->get_health());
	}

	void Scene::update(uint32_t time) {
		character_handler::update(time);
	}

	void Scene::inputs() {
		changed = buttons ^ last_buttons;

		if (buttons & changed & Button::DPAD_UP) {
			attack_menu::cursor_up();
		} else if (buttons & changed & Button::DPAD_DOWN) {
			attack_menu::cursor_down();
		} else if (buttons & changed & Button::A) {
			attack_menu::cursor_press();
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