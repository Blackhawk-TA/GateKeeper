#include "game.hpp"
#include "assets.hpp"
#include "game_scene.hpp"
#include "menu_scene.hpp"

using namespace blit;

MenuScene *menu_scene = nullptr;
GameScene *game_scene = nullptr;

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// This is called when starting the game.
//
void init() {
	set_screen_mode(ScreenMode::hires);
	load_persistent_spritesheets();

	transition::init();

	menu_scene = new MenuScene();
}

//TODO either implement own gameover screen or fix invalid read.
// without transition, there are invalid reads and writes. Transitions somehow fix it
void load_menu_scene() {
	transition::start([] {
		delete game_scene;
		game_scene = nullptr;
		menu_scene = new MenuScene();
	});
}

void load_game_scene(uint8_t save_id) {
	transition::start([save_id] {
		delete menu_scene;
		menu_scene = nullptr;
		game_scene = new GameScene(save_id);
	});
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {
	screen.clear();

	if (menu_scene != nullptr) {
		menu_scene->render(time);
	} else if (game_scene != nullptr) {
		game_scene->render(time);
	}

	if (transition::in_progress()) {
		transition::draw();
	}
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	if (menu_scene != nullptr) {
		menu_scene->update(time);
	} else if (game_scene != nullptr) {
		game_scene->update(time);
	}
}
