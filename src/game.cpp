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
	map::set_flag(map::TileFlags::DOOR, {773, 1336});

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
	if (buttons != last_buttons) {
		holding_button = !holding_button;
	}

	if (changed && !holding_button && (last_buttons & Button::DPAD_UP || last_buttons & Button::DPAD_DOWN
	|| last_buttons & Button::DPAD_LEFT || last_buttons & Button::DPAD_RIGHT)){
		Player::stop_movement();
	}

	if (buttons & Button::DPAD_UP) {
		player->move_up();
	} else if (buttons & Button::DPAD_DOWN) {
		player->move_down();
	} else if (buttons & Button::DPAD_LEFT) {
		player->move_left();
	} else if (buttons & Button::DPAD_RIGHT) {
		player->move_right();
	}

	last_buttons = buttons;

	//Handle camera_position update
	camera->update_position();
}
