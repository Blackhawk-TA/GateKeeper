#include "game.hpp"
#include "assets.hpp"
#include "camera.hpp"
#include "map/map_handler.hpp"
#include "utils/ui_overlay.hpp"
#include "player.hpp"

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

	map::load(map::MapTypes::EXTERIOR);

	//TODO set flags depending on map type, maybe map class is required
	map::set_flags(map::TileFlags::SOLID, {69, 70, 133, 134, 197, 198, 199, 261, 262, 263, 325, 326, 327, 705, 769});

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
	//Handler button inputs
	static uint32_t last_buttons = 0; //TODO check
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::DPAD_UP) {
		player->move_up();
		map::load(map::MapTypes::EXTERIOR);
	} else if (buttons & changed & Button::DPAD_DOWN) {
		player->move_down();
		map::load(map::MapTypes::WINTER);
	} else if (buttons & changed & Button::DPAD_LEFT) {
		player->move_left();
	} else if (buttons & changed & Button::DPAD_RIGHT) {
		player->move_right();
	}

	last_buttons = buttons;

	//Handle camera_position update
	camera->update_position();
}
