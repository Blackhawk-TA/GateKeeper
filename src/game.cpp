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

void load_menu_scene() {
//	transition::start([] {
		menu_scene = new MenuScene();
		delete game_scene;
		game_scene = nullptr;
//	});
}

void load_game_scene(uint8_t save_id) {
//	transition::start([] {
		game_scene = new GameScene(save_id);
		delete menu_scene;
		menu_scene = nullptr;
//	});
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
