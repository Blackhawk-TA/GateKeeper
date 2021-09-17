#include "game.hpp"
#include "assets.hpp"
#include "engine/camera.hpp"
#include "engine/map.hpp"
#include "utils/ui_overlay.hpp"
#include "player.hpp"
#include "engine/transition.hpp"
#include "engine/flags.hpp"

using namespace blit;

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

	flags::set_flag(flags::TileFlags::WALKABLE, {68, 69, 70, 71, 133, 134, 135, 197, 198, 199, 261, 262, 263, 325, 326, 327, 705, 769, 1037, 1038, 1101, 1102, 1165, 1166, 1167, 1229, 1230, 1231, 1293, 1294, 1295, 1632, 1633, 1634, 1635, 1636, 1637});
	flags::set_flag(flags::TileFlags::DOOR, {141, 517, 773, 965, 1573});
	map::load_section(map::MapSections::GRASSLAND);

	Point start_position = Point(22,12) - get_screen_tiles() / 2;
	camera = new Camera(start_position);
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

	if (transition::in_progress()) {
		transition::draw();
	}

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
	static bool holding_button = false;

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
