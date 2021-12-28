#pragma once
#include "32blit.hpp"
#include "engine/map.hpp"

enum SceneType {
	MENU = 1,
	GAME = 2,
	OPTIONS = 3,
	COMBAT = 4,
};

void load_previous_scene(uint8_t save_id = 0);
void load_scene(SceneType scene_type, uint8_t save_id = 0, map::MapSections map_section = map::NO_MAP);
