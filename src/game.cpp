#include "game.hpp"
#include "assets.hpp"
#include "scenes/game/game_scene.hpp"
#include "scenes/menu/menu_scene.hpp"
#include "scenes/options/options_scene.hpp"
#include "utils/saves/options.hpp"
#include "engine/effects/transition.hpp"
#include "scenes/game/ui/overlay.hpp"
#include "scenes/combat/combat_scene.hpp"

using namespace blit;

uint32_t ms_start = 0;
uint32_t ms_end = 0;
IScene *scene = nullptr;
Scene previous_scene;
Scene current_scene;

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// This is called when starting the game.
//
void init() {
	set_screen_mode(ScreenMode::hires);
	load_persistent_spritesheets();

	options::load();
	transition::init();

	scene = new MenuScene();
	current_scene = Scene::MENU;
}

void load_previous_scene(uint8_t save_id) {
	load_scene(previous_scene, save_id);
}

//TODO either implement own gameover screen or fix invalid read.
// without transition, there are invalid reads and writes. Transitions somehow fix it
void load_scene(Scene scene_type, uint8_t save_id, map::MapSections map_section) {
	previous_scene = current_scene;
	current_scene = scene_type;

	transition::start([scene_type, save_id, map_section] {
		delete scene;

		switch (scene_type) {
			case Scene::MENU:
				scene = new MenuScene();
				break;
			case Scene::GAME:
				scene = new GameScene(save_id);
				break;
			case Scene::OPTIONS:
				scene = new OptionsScene(save_id);
				break;
			case Scene::COMBAT:
				scene = new CombatScene(map_section);
				break;
		}
	});
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the
// amount of milliseconds elapsed since the start of your game
//
void render(uint32_t time) {
	ms_start = now();

	screen.clear();
	scene->render(time);

	if (transition::in_progress()) {
		transition::draw();
	}

	ms_end = now();
	draw_fps(ms_start, ms_end);
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount of milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	scene->update(time);

	//Only update inputs when not in transition
	if (!transition::in_progress()) {
		scene->inputs();
	}
}
