//
// Created by daniel on 24.09.21.
//

#include "savegame.hpp"
#include "options.hpp"
#include "../game_time.hpp"
#include "save_types.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"


/**
 * Gets all game object saves by merging the old ones from different map sections with the ones im memory from the current map section.
 * This is necessary because there are never all game objects in memory.
 * @param save_id The id of the current save
 * @return A full list of game object saves
 */
//TODO causes crash when on pico sometimes when going to snowland, solution: maybe one game_object save slot per map section
// it works for items, why not for game objects?

//TODO move to gameobject handler?
std::array<game::GameObject::Save, MAX_GAME_OBJECTS> get_game_object_saves(uint8_t save_id) {
	//The game object data which is currently in memory from the current map section
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> current_game_objects = game::game_objects::get_saves();

	//Load old save to fetch game object data that is not currently in memory
	save::SaveData old_save = {};
	bool save_found = read_save(old_save, save_id);
	bool game_object_save_exists;
	uint8_t i;

	if (save_found) {
		for (auto &current_game_object : current_game_objects) {
			if (game::game_objects::is_empty_signature(current_game_object.signature)) {
				continue;
			}

			game_object_save_exists = false;
			i = 0;

			//Update existing game object save if it exists
			while (!game_object_save_exists && i < old_save.game_objects.size()) {
				if (game::game_objects::has_equal_signature(old_save.game_objects.at(i).signature, current_game_object.signature)) {
					old_save.game_objects.at(i) = current_game_object;
					game_object_save_exists = true;
				}
				i++;
			}

			//Add new game object save to existing save
			if (!game_object_save_exists) {
				for (auto &old_game_object: old_save.game_objects) {
					if (game::game_objects::is_empty_signature(old_game_object.signature)) {
						old_game_object = current_game_object;
						break;
					}
				}
			}
		}
	} else {
		old_save.game_objects = current_game_objects;
	}

	//Return overwritten game objects
	return old_save.game_objects;
}

//TODO refactor
PlayerTempData get_player_temp_data(SaveOptions options, save::SaveData save_data) {
	//The default save data if it was not a tmp save for the combat scene
	PlayerTempData player_data = {
		save_data.map_section,
		save_data.player_data.direction,
		save_data.camera_position,
		save_data.player_data.health,
		{}
	};

	//On tmp save manually overwrite player_data depending on the outcome of the fight in the combat scene
	if (options.tmp_save && options.game_data.health == 0 && !options.game_data.won) { //Loss
		player_data = {
			map::INTERIOR,
			MovementDirection::DOWN,
			Point(45, 20),
			combat::Character::MAX_HEALTH,
			{}
		};
	} else if (options.tmp_save && options.game_data.health > 0 && !options.game_data.won) { //Escape
		player_data.direction = invert_direction(calculate_direction_from_points(save_data.previous_camera_position, save_data.camera_position));
		player_data.camera_position = save_data.previous_camera_position;
		player_data.health = options.game_data.health;
	} else if (options.tmp_save && options.game_data.won) { //Win
		player_data.health = options.game_data.health;
		player_data.enemy_signature = options.game_data.enemy_signature;
	}

	return player_data;
}

game::Player *savegame::create(uint8_t save_id) {
	Point start_position = Point(22, 13);

	map::load_section(map::GRASSLAND);
	camera::init(start_position);
	game::sidemenu::init(save_id);
	game::game_objects::init(map::GRASSLAND, save_id);
	game_time::init();

	return new game::Player(save::PlayerData{}, save_id);
}

bool savegame::convert_tmp_save(uint8_t save_id) {
	save::SaveData save_data;
	bool save_found = read_save(save_data, TMP_SAVE_ID);

	if (save_found) {
		write_save(save_data, save_id);
	}

	return save_found;
}

void savegame::save(uint8_t save_id, bool tmp_save) {
	//Check if current save is a new save game and therefore update save_count
	if (!tmp_save && options::save_count < save_id) {
		options::save_count = save_id;
		options::save();
	}

	//Save and compress data which will be saved
	save::SaveData save_data = {
		savegame::VERSION,
		map::get_section(),
		camera::get_player_position(),
		camera::get_previous_player_position(),
		game::Player::get_save(),
		get_game_object_saves(save_id),
		game::sidemenu::get_saves(),
		game_time::get_time()
	};

	if (tmp_save) {
		write_save(save_data, TMP_SAVE_ID);
	} else {
		write_save(save_data, save_id);
	}
}

game::Player *savegame::load(uint8_t save_id, SaveOptions options) {
	game::Player *player;
	save::SaveData save_data;
	uint8_t load_save_id = options.tmp_save ? TMP_SAVE_ID : save_id;

	bool save_found = read_save(save_data, load_save_id);

	//Load data from save game
	if (save_found) {
		if (save_data.version != savegame::VERSION) {
			//TODO port save using structs for each save version
		}

		//Load the player temp data required for setting health, position and map section
		PlayerTempData player_temp_data = get_player_temp_data(options, save_data);

		//Load the map section
		map::load_section(player_temp_data.map_section);

		//Load position and direction
		camera::init(player_temp_data.camera_position);

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
			game::game_objects::delete_game_object(player_temp_data.enemy_signature);
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

std::array<game::GameObject::Save, MAX_GAME_OBJECTS> savegame::load_game_objects(uint8_t save_id) {
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects;
	save::SaveData save_game;

	bool save_found = read_save(save_game, save_id);
	if (save_found) {
		game_objects = save_game.game_objects;
	}

	return game_objects;
}