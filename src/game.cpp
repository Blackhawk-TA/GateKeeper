#include "game.hpp"
#include "assets.hpp"
#include "camera.hpp"
#include "map/map_flags.hpp"
#include "map/map.hpp"
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
	screen.sprites = Surface::load_read_only(asset_spritesheet);

	map::generate_flags();
	map::load_section(map::MapSections::EXTERIOR);

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
		map::load_section(map::MapSections::EXTERIOR);
	} else if (buttons & changed & Button::DPAD_DOWN) {
		player->move_down();
		map::load_section(map::MapSections::WINTER);
	} else if (buttons & changed & Button::DPAD_LEFT) {
		player->move_left();
	} else if (buttons & changed & Button::DPAD_RIGHT) {
		player->move_right();
	}

	last_buttons = buttons;

	//Handle camera_position update
	camera->update_position();
}
