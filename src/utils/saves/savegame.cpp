//
// Created by daniel on 24.09.21.
//

#include "savegame.hpp"
#include "options.hpp"
#include "../game_time.hpp"
#include "save_types.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"
#include "../../scenes/game/game_objects/handler/save_game_objects.hpp"

namespace savegame {
	PlayerTempData get_player_temp_data(SaveOptions options, save::SaveData save_data) {
		//The default save data if it was not a tmp save for the combat scene
		PlayerTempData player_data = {
			save_data.map_section,
			save_data.player_data.direction,
			save_data.camera_position,
			save_data.previous_camera_position,
			save_data.player_data.health,
			{}
		};

		//On tmp save manually overwrite player_data depending on the outcome of the fight in the combat scene
		if (options.tmp_save && options.game_data.health == 0 && !options.game_data.won) { //Loss
			player_data = {
				map::INTERIOR,
				MovementDirection::DOWN,
				Point(45, 20),
				Point(45, 20),
				combat::Character::MAX_HEALTH,
				{}
			};
		} else if (options.tmp_save && options.game_data.health > 0 && !options.game_data.won) { //Escape
			player_data.direction = invert_direction(
				calculate_direction_from_points(save_data.previous_camera_position, save_data.camera_position));
			player_data.camera_position = save_data.previous_camera_position;
			player_data.health = options.game_data.health;
		} else if (options.tmp_save && options.game_data.won) { //Win
			player_data.health = options.game_data.health;
			player_data.enemy_signature = options.game_data.enemy_signature;
		}

		return player_data;
	}

	game::Player *create(uint8_t save_id) {
		Point start_position = Point(22, 13);

		map::load_section(map::GRASSLAND);
		camera::init(start_position);
		game::sidemenu::init(save_id);
		game::game_objects::init(map::GRASSLAND, save_id);
		game_time::init();

		return new game::Player(save::PlayerData{}, save_id);
	}

	bool convert_tmp_save(uint8_t save_id) {
		save::SaveData save_data;
		bool save_found = read_save(save_data, TMP_SAVE_ID);

		if (save_found) {
			write_save(save_data, save_id);
		}

		return save_found;
	}

	void save(uint8_t save_id, bool tmp_save) {
		//Check if current save is a new save game and therefore update save_count
		if (!tmp_save && options::save_count < save_id) {
			options::save_count = save_id;
			options::save();
		}

		//Save and compress data which will be saved
		save::SaveData save_data = {
			VERSION,
			map::get_section(),
			camera::get_player_position(),
			camera::get_previous_player_position(),
			game::Player::get_save(),
			game::game_objects::get_global_saves(save_id),
			game::sidemenu::get_saves(),
			game_time::get_time()
		};

		if (tmp_save) {
			write_save(save_data, TMP_SAVE_ID);
		} else {
			write_save(save_data, save_id);
		}
	}

	game::Player *load(uint8_t save_id, SaveOptions options) {
		game::Player *player;
		save::SaveData save_data;
		uint8_t load_save_id = options.tmp_save ? TMP_SAVE_ID : save_id;

		bool save_found = read_save(save_data, load_save_id);

		//Load data from save game
		if (save_found) {
			if (save_data.version != VERSION) {
				//TODO port save using structs for each save version
			}

			//Load the player temp data required for setting health, position and map section
			PlayerTempData player_temp_data = get_player_temp_data(options, save_data);

			//Load the map section
			map::load_section(player_temp_data.map_section);

			//Load position and direction
			camera::init(player_temp_data.camera_position);
			camera::set_previous_position(save_data.previous_camera_position);

			save::PlayerData player_save = save_data.player_data;
			player_save.direction = player_temp_data.direction;
			player_save.health = player_temp_data.health;
			player = new game::Player(player_save, save_id);

			//Init sidemenu
			game::sidemenu::init(save_id);

			//Load inventories
			game::sidemenu::load_saves(save_data.items);

			//Load game object states
			game::game_objects::init(player_temp_data.map_section, save_id);
			game::game_objects::load_saves(save_data.game_objects);
			if (!game::game_objects::is_empty_signature(player_temp_data.enemy_signature)) {
				game::game_objects::set_active(player_temp_data.enemy_signature, false);
			}

			//Load game time
			game_time::init();
			game_time::load(save_data.passed_time);
		} else {
			//If loading save was not successful, create new save
			player = create(save_id);
		}

		return player; //TODO with player save and load function there is no need to return this
	}

	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> load_game_objects(uint8_t save_id) {
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects;
		save::SaveData save_game;

		bool save_found = read_save(save_game, save_id);
		if (save_found) {
			game_objects = save_game.game_objects;
		}

		return game_objects;
	}
}
