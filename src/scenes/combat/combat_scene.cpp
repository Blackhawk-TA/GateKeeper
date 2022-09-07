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

	Scene::Scene(const SceneOptions& options) {
		map_section = options.combat_data.map_section;
		load_combat_scene();

		character_handler::init(options.save_id, options.combat_data);
		enemy = character_handler::get_enemy();
		player = character_handler::get_player();
		changed = 0;
		last_buttons = 0;

		attack_menu::init(options.save_id, player, enemy);
		player->start_round();
	}

	Scene::~Scene() {
		character_handler::cleanup();
		attack_menu::cleanup();

		//Deleted by character_handler
		player = nullptr;
		enemy = nullptr;
	}

	void Scene::render(uint32_t time) {
		map::draw();
		character_handler::draw();
		stats::draw_player_stats(player->get_health(), player->get_max_health(), player->get_stamina(), player->get_level());
		stats::draw_enemy_stats(enemy->get_health(), enemy->get_max_health(), enemy->get_level());

		if (attack_menu::is_open()) {
			attack_menu::draw();
		}
	}

	void Scene::update(uint32_t time) {
		character_handler::update(time);
	}

	void Scene::inputs() {
		if (!attack_menu::is_open()) return;

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
			case map::GRASSLAND:
				map::load_section(map::GRASSLAND_COMBAT);
				break;
			case map::DUNGEON:
				map::load_section(map::DUNGEON_COMBAT);
				break;
			case map::VOLCANO:
				map::load_section(map::VOLCANO_COMBAT);
				break;
			case map::SNOWLAND:
				map::load_section(map::SNOWLAND_COMBAT);
				break;
			case map::DESERT:
				map::load_section(map::DESERT_COMBAT);
				break;
			case map::CASTLE:
				map::load_section(map::CASTLE_COMBAT);
				break;
			case map::TOWER:
				map::load_section(map::TOWER_COMBAT);
				break;
			default:
				std::cerr << "No matching combat area for map section found" << std::endl;
				exit(1);
		}
		camera::set_position(Point(15, 12));
	}
}