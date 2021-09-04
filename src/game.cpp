#include "game.hpp"
#include "assets.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "utils/ui_overlay.hpp"
#include "player.hpp"

using namespace blit;

uint32_t last_buttons = 0;
uint32_t changed = 0;
bool holding_button = false;

uint32_t ms_start, ms_end;
Camera *camera;
Player *player;

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// This is called when starting the game.
//
void init() {
	set_screen_mode(ScreenMode::hires);
	screen.sprites = Surface::load_read_only(asset_spritesheet);

	map::load_section(map::MapSections::EXTERIOR);
	map::set_flag(map::TileFlags::SOLID, {768});
	map::set_flag(map::TileFlags::DOOR, {773, 1253, 1254});

	camera = new Camera();
	player = new Player(camera);
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

	map::draw(camera->get_screen_position());
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
	//Handle button inputs
	changed = buttons ^ last_buttons;

	//Check if the player is holding a button
	holding_button = buttons == last_buttons;

	if (changed && !holding_button && (last_buttons & Button::DPAD_UP || last_buttons & Button::DPAD_DOWN
	|| last_buttons & Button::DPAD_LEFT || last_buttons & Button::DPAD_RIGHT)){
		Player::stop_movement();
	}

	if (buttons & Button::DPAD_UP) {
		player->move(player->UP);
	} else if (buttons & Button::DPAD_DOWN) {
		player->move(player->DOWN);
	} else if (buttons & Button::DPAD_LEFT) {
		player->move(player->LEFT);
	} else if (buttons & Button::DPAD_RIGHT) {
		player->move(player->RIGHT);
	}

	last_buttons = buttons;

	//Handle camera_position update
	camera->update_position();
}
