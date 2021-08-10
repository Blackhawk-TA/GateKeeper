#include "game.hpp"

using namespace blit;

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// This is called when starting the game.
//
void init() {
	set_screen_mode(ScreenMode::hires);
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
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
}