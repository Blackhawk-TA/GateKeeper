//
// Created by daniel on 17.10.21.
//

#include "game_scene.hpp"
#include "../../engine/flags.hpp"
#include "../../utils/saves/savegame.hpp"
#include "ui/overlay.hpp"
#include "../../utils/game_time.hpp"
#include "utils/utils.hpp"
#include "ui/sidemenu.hpp"

namespace game {
	Scene::Scene(const SceneOptions& options) {
		Scene::save_id = options.save_id;
		last_buttons = 0;
		changed = 0;

		flags::set_flags(flags::TileFlags::WALKABLE, {
			33, 68, 69, 70, 71, 133, 134, 135, 197, 198, 199, 261, 262, 263, 325, 326, 327, 640, 641, 705, 712, 713,
			769, 776, 840, 841, 968, 1029, 1030, 1037, 1038, 1093, 1094, 1101, 1102, 1157, 1158, 1159, 1165, 1166, 1167,
			1221, 1222, 1223, 1229, 1230, 1231, 1263, 1264, 1265, 1285, 1286, 1287, 1293, 1294, 1295, 1327, 1328, 1329,
			1391, 1392, 1393, 1504, 1568, 1632, 1633, 1634, 1635, 1636, 1637, 2053, 2054, 2055, 2097, 2114, 2117, 2118, 2119,
			2161, 2181, 2182, 2183, 2241, 2251, 2281, 2282, 2305, 2315, 2345, 2346, 2376, 2377, 2378, 2409, 2410, 2440,
			2441, 2473, 2474, 2477, 2504, 2505, 2506, 2528, 2529, 2540, 2541, 2542, 2568, 2569, 2570, 2592, 2593, 2605,
			2632, 2633, 2634, 2656, 2657, 2720, 2721, 2784, 2785, 2848, 2849, 3180, 3181, 3182, 3183, 3185, 3186, 3189,
			3190, 3244, 3245, 3246, 3247, 3248, 3249, 3250, 3251, 3252, 3253, 3254, 3255, 3308, 3309, 3310, 3311, 3312,
			3313, 3314, 3315, 3316, 3317, 3318, 3319, 3372, 3373, 3374, 3375, 3376, 3377, 3378, 3379, 3380, 3381, 3382,
			3383, 3436, 3437, 3438, 3439, 3441, 3442, 3445, 3446, 3477, 3851, 3852, 3853, 3854, 3912, 3913, 3914, 3915,
			3916, 3917, 3918, 3979, 3980, 3981, 3982, 4044, 4045
		});
		flags::set_flags(flags::TileFlags::ELEVATE_1PX, {1492, 1494});
		flags::set_flags(flags::TileFlags::ELEVATE_2PX, {1493});
		flags::set_flags(flags::TileFlags::ELEVATE_3PX, {186, 2861});
		flags::set_flags(flags::TileFlags::ENTRY, {
			141, 294, 295, 515, 517, 773, 965, 1425, 1573, 1997, 2371, 2373, 2629, 2821
		});
		flags::set_flags(flags::TileFlags::DEADLY, {
			56, 57, 58, 248, 249, 250, 3497, 3498, 3560, 3561, 3562, 3563, 3624, 3625, 3626, 3627, 3688, 3689, 3690,
			3691, 3753, 3754
		});

		SaveOptions save_options = {
			options.tmp_save,
			options.game_data
		};
		player = savegame::load(save_id, save_options);
	}

	Scene::~Scene() {
		//Auto save
		if (!Player::is_dead()) {
			if (Player::in_cut_scene()) {
				//When changing scene on cut scene create temporary save
				savegame::save(save_id, true);
			} else {
				savegame::save(save_id);
			}
		}
		delete player;

		//Delete game objects and inventory after saving
		game_objects::cleanup();
		sidemenu::cleanup();
	}

	void Scene::render(uint32_t time) {
		map::draw();

		game_objects::draw_under_player();
		player->draw();
		game_objects::draw_over_player();
		game_objects::draw_textbox();

		overlay::draw_statusbar(Player::get_health());

		if (sidemenu::is_open()) {
			sidemenu::draw();
		}
	}

	void Scene::update(uint32_t time) {
		game_time::update(time);

		//Handle camera_position update
		camera::update_position();

		//Handle stargate animations
		game_objects::update(time);
	}

	void Scene::inputs() {
		changed = buttons ^ last_buttons;

		if (sidemenu::is_open()) {
			if (buttons & changed & Button::DPAD_UP) {
				sidemenu::cursor_up();
			} else if (buttons & changed & Button::DPAD_DOWN) {
				sidemenu::cursor_down();
			} else if (buttons & changed & Button::A) {
				sidemenu::cursor_press();
			} else if (buttons & changed & Button::B) {
				sidemenu::navigate_back();
			} else if (buttons & changed & Button::MENU || buttons & changed & Button::Y) {
				sidemenu::close();
			}
		} else if (game_objects::is_textbox_open()) {
			if ((buttons & changed & Button::A) && !game_objects::next_textbox()) {
				game_objects::close_textboxes();
			}
		} else {
			if (buttons & Button::DPAD_UP) {
				player->move(UP);
			} else if (buttons & Button::DPAD_DOWN) {
				player->move(DOWN);
			} else if (buttons & Button::DPAD_LEFT) {
				player->move(LEFT);
			} else if (buttons & Button::DPAD_RIGHT) {
				player->move(RIGHT);
			} else if (buttons & changed & Button::MENU || buttons & changed & Button::Y) {
				sidemenu::open(sidemenu::MAIN);
			} else if (buttons & changed & Button::A) {
				game_objects::player_interact();
			}
		}

		last_buttons = buttons;
	}
}