#include "game.hpp"
#include "assets.hpp"
#include "utils/map.hpp"
#include "utils/ui_overlay.hpp"

using namespace blit;

uint32_t ms_start, ms_end;

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
Vec2 position = Vec2(0, 0); //TODO implement properly with player class
void render(uint32_t time) {
	ms_start = now();

	screen.clear();
	map::draw(position);

	ms_end = now();
	ui_overlay::draw_fps(ms_start, ms_end);
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	static uint32_t last_buttons = 0;
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::DPAD_UP) {
		position.y -= 0.25;
	} else if (buttons & changed & Button::DPAD_DOWN) {
		position.y += 0.25;
	} else if (buttons & changed & Button::DPAD_LEFT) {
		position.x -= 0.25;
	} else if (buttons & changed & Button::DPAD_RIGHT) {
		position.x += 0.25;
	}

	last_buttons = buttons;
}