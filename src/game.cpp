#include <iostream>
#include "game.hpp"
#include "assets.hpp"
#include "scenes/game/game_scene.hpp"
#include "scenes/menu/menu_scene.hpp"
#include "scenes/options/options_scene.hpp"
#include "engine/effects/transition.hpp"
#include "scenes/game/ui/overlay.hpp"
#include "scenes/combat/combat_scene.hpp"
#include "scenes/gameover/gameover_scene.hpp"

using namespace blit;

uint32_t ms_end = 0;
IScene *scene = nullptr;
SceneType previous_scene;
SceneType current_scene;

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// This is called when starting the game.
//
void init() {
	set_screen_mode(ScreenMode::hires);
	load_persistent_spritesheets();

	scene = new menu::Scene();
	current_scene = SceneType::MENU;
}

SceneType get_previous_scene() {
	return previous_scene;
}

void load_previous_scene(uint8_t save_id) {
	SceneOptions options = {
		save_id,
	};
	load_scene(previous_scene, options);
}

//TODO either implement own gameover screen or fix invalid read.
// without transition, there are invalid reads and writes. Transitions somehow fix it
void load_scene(SceneType scene_type, const SceneOptions& options) {
	previous_scene = current_scene;
	current_scene = scene_type;

	transition::start([scene_type, options] {
		delete scene;

		switch (scene_type) {
			case SceneType::MENU:
				scene = new menu::Scene();
				break;
			case SceneType::GAME:
				scene = new game::Scene(options);
				break;
			case SceneType::OPTIONS:
				scene = new options::Scene(options);
				break;
			case SceneType::COMBAT:
				scene = new combat::Scene(options);
				break;
			case SceneType::GAMEOVER:
				scene = new gameover::Scene(options);
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
	screen.clear();
	scene->render(time);

	if (transition::in_process()) {
		transition::draw();
	}

	draw_fps(time, ms_end);
	ms_end = now();
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
	transition::update(time);

	//Only update inputs when not in transition
	if (!transition::in_process()) {
		scene->inputs();
	}
}
