#include "32blit.hpp"

enum Scene {
	MENU = 1,
	GAME = 2,
	SETTINGS = 3
};

void load_scene(Scene scene_type, uint8_t save_id = 0);
