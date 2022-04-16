//
// Created by daniel on 24.09.21.
//

#include "savegame.hpp"
#include "options.hpp"
#include "../game_time.hpp"
#include "save_types.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"
#include "../../scenes/game/game_objects/handler/save_game_objects.hpp"
#include "../../scenes/game/game_objects/handler/player_handler.hpp"
#include "../../scenes/game/ui/overlay.hpp"
#include "../../scenes/game/ui/notification.hpp"
#include "../../scenes/game/game_objects/handler/extensions/enemy_handler.hpp"

namespace savegame {
	PlayerTempData get_player_temp_data(GameData game_data, save::SaveData save_data) {
		//The default save data if it was not a tmp save for the combat scene
		PlayerTempData player_data = {
			save_data.map_section,
			save_data.player_data.direction,
			save_data.camera_position,
			save_data.previous_camera_position,
			save_data.player_data.health,
			save_data.player_data.story_state,
			{}
		};

		//On tmp save manually overwrite player_data depending on the outcome of the fight in the combat scene or death by world
		if (game_data.health == 0 && !game_data.won_fight && game_data.respawn) { //Loss + death by world
			StoryState story_state = save_data.player_data.story_state;

			if (save_data.map_section == map::DESERT && save_data.player_data.story_state == START) {
				story_state = FIRST_DEATH;
			}

			player_data = {
				map::INTERIOR,
				MovementDirection::DOWN,
				Point(45, 20),
				Point(45, 20),
				game::Player::MAX_HEALTH,
				story_state
			};
		} else if (options::active_tmp_save != 0 && game_data.health > 0 && !game_data.won_fight && !game_data.respawn) { //Escape
			player_data.direction = invert_direction(calculate_direction_from_points(save_data.previous_camera_position, save_data.camera_position));
			player_data.camera_position = save_data.previous_camera_position;
			player_data.health = game_data.health;
		} else if (options::active_tmp_save != 0 && game_data.won_fight && !game_data.respawn) { //Win
			player_data.health = game_data.health;
			player_data.enemy_signature = game_data.enemy_signature;
		} else if (options::active_tmp_save != 0 && game_data.won_fight && game_data.respawn) { //Win + finished game (detected by won + respawn)
			player_data = {
				map::INTERIOR,
				MovementDirection::RIGHT,
				Point(1, 23),
				Point(1, 23),
				game::Player::MAX_HEALTH,
				COMPLETED,
				player_data.enemy_signature,
			};
		}

		return player_data;
	}

	void create(uint8_t save_id) {
		Point start_position = Point(1, 23);

		map::load_section(map::INTERIOR);
		camera::init(start_position);
		game::sidemenu::init(save_id);
		game::game_objects::init(map::INTERIOR, save_id, StoryState::START);
		game_time::init();
		game::player_handler::load_save(save::PlayerData{
			100,
			1,
			0,
			0,
			0,
			RIGHT,
			StoryState::START,
		});
	}

	bool convert_tmp_save(uint8_t save_id) {
		save::SaveData save_data;
		bool save_found = read_save(save_data, TMP_SAVE_ID);

		if (save_found) {
			write_save(save_data, save_id);
		}
		options::active_tmp_save = 0;
		options::save();

		return save_found;
	}

	void save(uint8_t save_id, bool tmp_save) {
		if (!tmp_save) {
			//Check if current save is a new save game and therefore update save_count
			if (options::save_count < save_id) {
				options::save_count = save_id;
			}
		} else {
			//Save the id when going to a tmp save to restore it on unexpected combat scene exit
			options::active_tmp_save = save_id;
		}
		options::save();

		//Save and compress data which will be saved
		save::SaveData save_data = {
			VERSION,
			map::get_section(),
			camera::get_player_position(),
			camera::get_previous_player_position(),
			game::player_handler::get_save(),
			game::game_objects::get_global_saves(save_id),
			game::sidemenu::get_saves(),
			game_time::get_time()
		};

		if (tmp_save) {
			write_save(save_data, TMP_SAVE_ID);
		} else {
			write_save(save_data, save_id);
		}

		//Show save icon
		game::notification::add_to_queue(game::notification::Icon::SAVE);
	}

	void load(uint8_t save_id, GameData game_data) {
		save::SaveData save_data;
		uint8_t load_save_id = options::active_tmp_save != 0 ? TMP_SAVE_ID : save_id;

		bool save_found = read_save(save_data, load_save_id);

		//Load data from save game
		if (save_found) {
			if (save_data.version != VERSION) {
				//TODO port save using structs for each save version
			}

			//Load the player temp data required for setting health, position and map section
			PlayerTempData player_temp_data = get_player_temp_data(game_data, save_data);

			//Load the map section
			map::load_section(player_temp_data.map_section);

			//Load position and direction
			camera::init(player_temp_data.camera_position);
			camera::set_previous_position(save_data.previous_camera_position);

			//Init sidemenu
			game::sidemenu::init(save_id);

			//Load inventories
			game::sidemenu::load_saves(save_data.items);

			//Load game object states
			game::game_objects::init(player_temp_data.map_section, save_id, player_temp_data.story_state);
			game::game_objects::load_saves(save_data.game_objects, player_temp_data.story_state);
			if (!game::game_objects::is_empty_signature(player_temp_data.enemy_signature)) {
				game::game_objects::set_active(player_temp_data.enemy_signature, false);

				//Add XP gained during a fight
				game::Enemy *enemy = game::enemy_handler::get_enemy(player_temp_data.enemy_signature);
				float xp_modifier = sqrtf(enemy->get_level()) / sqrtf(save_data.player_data.level);
				save_data.player_data.gained_xp = static_cast<uint32_t>(static_cast<float>(blit::random() % 50 + 75) * xp_modifier);
			}

			//Load player save with health, level and direction
			game::player_handler::load_save(save::PlayerData{
				player_temp_data.health,
				save_data.player_data.level,
				save_data.player_data.xp,
				save_data.player_data.gained_xp,
				save_data.player_data.gold,
				player_temp_data.direction,
				player_temp_data.story_state,
			});

			//Load game time
			game_time::init();
			game_time::load(save_data.passed_time);
		} else {
			//If loading save was not successful, create new save
			create(save_id);
		}
	}

	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> load_game_objects(uint8_t save_id) {
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects;
		save::SaveData save_data;

		bool save_found = read_save(save_data, save_id);
		if (save_found) {
			game_objects = save_data.game_objects;
		}

		return game_objects;
	}
}
