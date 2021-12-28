//
// Created by daniel on 25.12.21.
//

#include <iostream>
#include "combat_scene.hpp"
#include "../../engine/camera.hpp"
#include "ui/combat_menu.hpp"
#include "ui/combat_stats.hpp"

namespace combat {
	//TODO use TMP_SAVE_ID when returning to game_scene
	Scene::Scene(map::MapSections map_section) {
		Scene::map_section = map_section;
		load_combat_scene();

		enemy = new Enemy();
		player = new CombatPlayer();

		menu::open();
	}

	Scene::~Scene() {
		delete enemy;
		delete player;
	};

	void Scene::render(uint32_t time) {
		map::draw();
		enemy->draw();
		player->draw();
		menu::draw();
		stats::draw(90, 100, 10);
	}

	void Scene::update(uint32_t time) {

	}

	void Scene::inputs() {

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