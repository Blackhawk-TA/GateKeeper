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

game::Player *savegame::create(uint8_t save_id) {
	Point start_position = Point(22, 12);

	map::load_section(map::MapSections::GRASSLAND);
	camera::init(start_position);
	game::sidemenu::init(save_id);
	game::inventory::init();
	game::game_objects::init();
	game_time::init();

	return new game::Player(game::Player::MovementDirection::DOWN, 100);
}

void savegame::save(uint8_t save_id) {
	//Check if current save is a new save game and therefore update save_count
	if (save_id != TMP_SAVE_ID && options::save_count < save_id) {
		options::save_count = save_id;
		options::save();
	}

	//Fetch item and stargate data
	//TODO handle item compression and decompression in inventory namespace in get_items and load
	std::vector<Listbox::Item> items = game::inventory::get_items();

	//Save and compress data which will be saved
	//TODO destroys existing saves if a new entry is added like a game_object => every update destroys savegames
	// Inconsistent array lengths cause this problem, if the length of an array changes, the old change gets overwritten
	auto game_data = GameData{
		map::get_section(),
		camera::get_player_position(),
		game::Player::get_direction(),
		game::Player::get_health(),
		game::game_objects::get_saves(),
		compress_items(items),
		game_time::get_time()
	};

	write_save(game_data, save_id);
}

game::Player *savegame::load(uint8_t save_id) {
	game::Player *player;
	GameData save_data;

	bool save_found = read_save(save_data, save_id);

	//Load data from save game
	if (save_found) {
		//Load position and direction
		map::load_section(save_data.map_section);
		camera::init(save_data.camera_position);
		player = new game::Player(save_data.player_direction, save_data.player_health);

		//Init sidemenu
		game::sidemenu::init(save_id);

		//Load inventory
		game::inventory::init();
		game::inventory::load(decompress_items(save_data.items));

		//Load game object states
		game::game_objects::init();
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
