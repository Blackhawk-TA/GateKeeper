//
// Created by daniel on 25.12.21.
//

#include <iostream>
#include "combat_scene.hpp"
#include "../../engine/camera.hpp"
#include "ui/combat_menu.hpp"

//TODO use TMP_SAVE_ID when returning to game_scene
CombatScene::CombatScene(map::MapSections map_section) {
	CombatScene::map_section = map_section;
	load_combat_scene();

	combat_menu::open();
}

CombatScene::~CombatScene() = default;

void CombatScene::render(uint32_t time) {
	map::draw();
	combat_menu::draw();
}

void CombatScene::update(uint32_t time) {

}

void CombatScene::inputs() {

}

void CombatScene::load_combat_scene() {
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
