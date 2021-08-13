#include "game.hpp"
#include "assets.hpp"
#include "utils/map.hpp"

using namespace blit;

Mat3 camera;
std::function<Mat3(uint8_t)> level_line_interrupt_callback = [](uint8_t y) -> Mat3 {
	return camera;
};

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// This is called when starting the game.
//
void init() {
	set_screen_mode(ScreenMode::hires);
	screen.sprites = Surface::load(asset_spritesheet);

	map::create();
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

	map::draw(&level_line_interrupt_callback);
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	camera = Mat3::identity();
}