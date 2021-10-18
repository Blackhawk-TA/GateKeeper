#include "game.hpp"
#include "assets.hpp"
#include "scenes/game_scene.hpp"
#include "scenes/menu_scene.hpp"

using namespace blit;

IScene *scene = nullptr;

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

	scene = new MenuScene();
}

//TODO either implement own gameover screen or fix invalid read.
// without transition, there are invalid reads and writes. Transitions somehow fix it
void load_menu_scene() {
	transition::start([] {
		delete scene;
		scene = new MenuScene();
	});
}

void load_game_scene(uint8_t save_id) {
	transition::start([save_id] {
		delete scene;
		scene = new GameScene(save_id);
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
	scene->render(time);

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
	scene->update(time);
}
