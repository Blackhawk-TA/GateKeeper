#include "game.hpp"
#include "assets.hpp"
#include "utils/map.hpp"
#include "utils/ui_overlay.hpp"
#include "player.hpp"

using namespace blit;

uint32_t ms_start, ms_end;
Player *player;
Point camera_position;

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
	map::set_flags(map::TileFlags::SOLID, {25, 26, 32, 33, 34, 40, 41, 42, 48});

	player = new Player();
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {
	ms_start = now();
	screen.clear();

	map::draw(camera_position);
	player->draw();

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
	//Handler button inputs
	static uint32_t last_buttons = 0;
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::DPAD_UP) {
		player->move_up();
	} else if (buttons & changed & Button::DPAD_DOWN) {
		player->move_down();
	} else if (buttons & changed & Button::DPAD_LEFT) {
		player->move_left();
	} else if (buttons & changed & Button::DPAD_RIGHT) {
		player->move_right();
	}

	last_buttons = buttons;

	//Handle camera update
	camera_position = player->update_camera();
}