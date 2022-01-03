//
// Created by daniel on 24.09.21.
//

#include "savegame.hpp"
#include "options.hpp"
#include "../../scenes/game/ui/inventory.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"
#include "../game_time.hpp"
#include <cassert>

/**
 * Parses the item vector into an array, because vector cannot be saved directly
 * @param items The item vector to be compressed
 * @return The compressed item array
 */
std::array<savegame::Item, MAX_ITEMS> compress_items(std::vector<Listbox::Item> &items) {
	std::array<savegame::Item, MAX_ITEMS> compressed_items = {};
	uint8_t amount;

	//TODO check earlier if possible
	assert(items.size() <= MAX_ITEMS);

	for (auto i = 0u; i < items.size(); i++) {
		amount = i < items.size() ? items[i].amount : 0;
		compressed_items[i] = savegame::Item{
			items[i].type,
			amount
		};
	}

	return compressed_items;
}

std::vector<Listbox::Item> decompress_items(std::array<savegame::Item, MAX_ITEMS> &items) {
	std::vector<Listbox::Item> decompressed_items = {};
	Listbox::Item item_template;

	uint8_t i = 0;
	savegame::Item *item;
	bool array_end = false;

	while (!array_end && i < MAX_ITEMS) {
		item = &items[i];

		if (item->type == 0 && item->amount == 0) {
			array_end = true;
			continue;
		}

		item_template = listbox_item::create_inventory_item(static_cast<listbox_item::INVENTORY_ITEM>(item->type));

		//Include only items that have an amount > 0 or are a menu item
		if (item->type > 0 && (item->amount > 0 || (item->amount == 0 && !item_template.single_use))) {
			decompressed_items.emplace_back(Listbox::Item{
				item->type,
				item_template.name,
				item_template.tooltip,
				item_template.callback_tooltip,
				item_template.callback_fail_tooltip,
				item_template.single_use,
				item->amount,
				item_template.callback
			});
		}
		i++;
	}

	return decompressed_items;
}

/**
 * Gets all game object saves by merging the old ones from different map sections with the ones im memory from the current map section.
 * This is necessary because there are never all game objects in memory.
 * @param save_id The id of the current save
 * @return A full list of game object saves
 */
//TODO causes crash when on pico sometimes when going to snowland, solution: maybe one game_object save slot per map section
// it works for items, why not for game objects?
std::array<game::GameObject::Save, MAX_GAME_OBJECTS> get_game_object_saves(uint8_t save_id) {
	//The game object data which is currently in memory from the current map section
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> current_game_objects = game::game_objects::get_saves();

	//Load old save to fetch game object data that is not currently in memory
	savegame::SaveData old_save = {};
	bool save_found = read_save(old_save, save_id);

	if (save_found) {
		for (auto &current_game_object : current_game_objects) {
			if (game::game_objects::is_empty_signature(current_game_object.signature)) {
				continue;
			}

			for (auto &old_game_object : old_save.game_objects) {
				if (game::game_objects::has_equal_signature(old_game_object.signature, current_game_object.signature)) {
					old_game_object = current_game_object;
					break;
				}
			}
		}
	} else {
		old_save.game_objects = current_game_objects;
	}

	//Return overwritten game objects
	return old_save.game_objects;
}

PlayerData get_player_data(SaveOptions options, savegame::SaveData save_data) {
	//The default save data if it was not a tmp save for the combat scene
	PlayerData player_data = {
		save_data.map_section,
		save_data.player_direction,
		save_data.camera_position,
		save_data.player_health,
	};

	//On tmp save manually overwrite player_data depending on the outcome of the fight in the combat scene
	if (options.tmp_save && options.game_data.health == 0 && !options.game_data.won) { //Loss
		//TODO add game over screen
		player_data = {
			map::INTERIOR,
			MovementDirection::DOWN,
			Point(45, 20),
			combat::Character::MAX_HEALTH,
		};
	} else if (options.tmp_save && options.game_data.health > 0 && !options.game_data.won) { //Escape
		player_data.direction = invert_direction(calculate_direction_from_points(save_data.previous_camera_position, save_data.camera_position));
		player_data.camera_position = save_data.previous_camera_position;
		player_data.health = options.game_data.health;
	} else if (options.tmp_save && options.game_data.won) { //Win
		//TODO delete enemy from game object collection
		player_data.health = options.game_data.health;
	}

	return player_data;
}

game::Player *savegame::create(uint8_t save_id) {
	Point start_position = Point(22, 12);

	map::load_section(map::GRASSLAND);
	camera::init(start_position);
	game::sidemenu::init(save_id);
	game::inventory::init();
	game::game_objects::init(map::GRASSLAND, save_id);
	game_time::init();

	return new game::Player(MovementDirection::DOWN, 100, save_id);
}

void savegame::save(uint8_t save_id, bool tmp_save) {
	//Check if current save is a new save game and therefore update save_count
	if (!tmp_save && options::save_count < save_id) {
		options::save_count = save_id;
		options::save();
	}

	//Fetch item and stargate data
	//TODO handle item compression and decompression in inventory namespace in get_items and load
	std::vector<Listbox::Item> items = game::inventory::get_items();

	//Save and compress data which will be saved
	SaveData save_data = {
		savegame::VERSION,
		map::get_section(),
		camera::get_player_position(),
		camera::get_previous_player_position(),
		game::Player::get_direction(),
		game::Player::get_health(),
		get_game_object_saves(save_id),
		compress_items(items),
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
	SaveData save_data;
	uint8_t load_save_id = options.tmp_save ? TMP_SAVE_ID : save_id;

	bool save_found = read_save(save_data, load_save_id);

	//Load data from save game
	if (save_found) {
		if (save_data.version != savegame::VERSION) {
			//TODO port save using structs for each save version
		}

		//Load the player data required for setting health, position and map section
		PlayerData player_data = get_player_data(options, save_data);

		//Load the map section
		map::load_section(player_data.map_section);

		//Load position and direction
		camera::init(player_data.camera_position);
		player = new game::Player(player_data.direction, player_data.health, save_id);

		//Init sidemenu
		game::sidemenu::init(save_id);

		//Load inventory
		game::inventory::init();
		game::inventory::load(decompress_items(save_data.items));

		//Load game object states
		game::game_objects::init(save_data.map_section, save_id);
		game::game_objects::load_saves(save_data.game_objects);

		//Load game time
		game_time::init();
		game_time::load(save_data.passed_time);
	} else {
		//If loading save was not successful, create new save
		player = create(save_id);
	}

	return player;
}

std::array<game::GameObject::Save, MAX_GAME_OBJECTS> savegame::load_game_objects(uint8_t save_id) {
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects;
	savegame::SaveData save_game;

	bool save_found = read_save(save_game, save_id);
	if (save_found) {
		game_objects = save_game.game_objects;
	}

	return game_objects;
}