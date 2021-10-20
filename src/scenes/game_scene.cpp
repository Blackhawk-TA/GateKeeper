//
// Created by daniel on 17.10.21.
//

#include "game_scene.hpp"
#include "../game.hpp"

GameScene::GameScene(uint8_t save_id) {
	GameScene::save_id = save_id;
	last_buttons = 0;
	changed = 0;
	ms_start = 0;
	ms_end = 0;

	flags::set_flag(flags::TileFlags::WALKABLE, {
		33, 68, 69, 70, 71, 133, 134, 135, 197, 198, 199, 261, 262, 263, 325, 326, 327, 640, 641, 705, 712, 713,
		769, 776, 840, 841, 968, 1029, 1030, 1037, 1038, 1093, 1094, 1101, 1102, 1157, 1158, 1159, 1165, 1166, 1167,
		1221, 1222, 1223, 1229, 1230, 1231, 1263, 1264, 1265, 1285, 1286, 1287, 1293, 1294, 1295, 1327, 1328, 1329,
		1391, 1392, 1393, 1504, 1632, 1633, 1634, 1635, 1636, 1637, 2305
	});
	flags::set_flag(flags::TileFlags::ELEVATE_1PX, {1492, 1494});
	flags::set_flag(flags::TileFlags::ELEVATE_2PX, {1493});
	flags::set_flag(flags::TileFlags::ELEVATE_3PX, {186});
	flags::set_flag(flags::TileFlags::ENTRY, {141, 294, 515, 517, 773, 965, 1425, 1573});
	flags::set_flag(flags::TileFlags::DEADLY, {57, 248, 249});
	map::load_section(map::MapSections::GRASSLAND);

	sidemenu::init(save_id);
	player = savegame::load(save_id);
}

GameScene::~GameScene() {
	savegame::save(save_id); //Auto save
	delete player;
}

void GameScene::render(uint32_t time) {
	ms_start = now();

	map::draw();
	stargate_handler::draw_stargates();
	player->draw();

	if (sidemenu::is_open()) {
		sidemenu::draw();
	}

	if (inventory::is_open()) {
		inventory::draw();
	}

	ms_end = now();
	overlay::draw_fps(ms_start, ms_end);
}

void GameScene::update(uint32_t time) {
	//Handle player death
	if (player->is_dead() && !transition::in_progress()) {
		load_scene(Scene::MENU);
	}

	//Handle camera_position update
	camera::update_position();

	//Handle stargate animations
	stargate_handler::update_animations();

	//Handle button inputs
	changed = buttons ^ last_buttons;

	if (sidemenu::is_open()) {
		if (buttons & changed & Button::DPAD_UP) {
			sidemenu::cursor_up();
		} else if (buttons & changed & Button::DPAD_DOWN) {
			sidemenu::cursor_down();
		} else if (buttons & changed & Button::A) {
			sidemenu::cursor_press();
		} else if (buttons & changed & Button::MENU || buttons & changed & Button::B) {
			sidemenu::close();
		}
	} else if (inventory::is_open()) {
		if (buttons & changed & Button::DPAD_UP) {
			inventory::cursor_up();
		} else if (buttons & changed & Button::DPAD_DOWN) {
			inventory::cursor_down();
		} else if (buttons & changed & Button::A) {
			inventory::cursor_press();
		} else if (buttons & changed & Button::B) {
			sidemenu::open();
			inventory::close();
		} else if (buttons & changed & Button::MENU) {
			inventory::close();
		} else if (buttons & changed & Button::X) {
			inventory::add_item(listbox_item::create_inventory_item(listbox_item::GATE_PART));
		}
	} else {
		if (buttons & Button::DPAD_UP) {
			player->move(player->UP);
		} else if (buttons & Button::DPAD_DOWN) {
			player->move(player->DOWN);
		} else if (buttons & Button::DPAD_LEFT) {
			player->move(player->LEFT);
		} else if (buttons & Button::DPAD_RIGHT) {
			player->move(player->RIGHT);
		} else if (buttons & changed & Button::MENU) {
			sidemenu::open();
		} else if (buttons & changed & Button::A) {
			player->attack();
		} else if (buttons & changed & Button::B) {
			player->evade();
		}
	}

	last_buttons = buttons;
}
