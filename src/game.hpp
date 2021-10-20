#pragma once
#include "32blit.hpp"

enum Scene {
	MENU = 1,
	GAME = 2,
	OPTIONS = 3
};

void load_previous_scene(uint8_t save_id = 0);
void load_scene(Scene scene_type, uint8_t save_id = 0);
