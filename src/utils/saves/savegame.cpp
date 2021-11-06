//
// Created by daniel on 24.09.21.
//

#include "savegame.hpp"
#include "options.hpp"
#include "../../scenes/game/ui/inventory.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"

/**
 * Parses the item vector into an array, because vector cannot be saved directly
 * @param items The item vector to be compressed
 * @return The compressed item array
 */
std::array<savegame::Item, listbox_item::INVENTORY_COUNTER> compress_items(std::vector<Listbox::Item> &items) {
	std::array<savegame::Item, listbox_item::INVENTORY_COUNTER> compressed_items = {};
	uint8_t amount;

	for (auto i = 0u; i < listbox_item::INVENTORY_COUNTER; i++) {
		amount = i < items.size() ? items [i].amount : 0;
		compressed_items[i] = savegame::Item{
			static_cast<listbox_item::INVENTORY_ITEM>(i + 1),
			amount
		};
	}

	return compressed_items;
}

std::vector<Listbox::Item> decompress_items(std::array<savegame::Item, listbox_item::INVENTORY_COUNTER> &items) {
	std::vector<Listbox::Item> decompressed_items = {};
	Listbox::Item item_template;

	for (auto i = 0u; i < items.size(); i++) {
		item_template = listbox_item::create_inventory_item(static_cast<listbox_item::INVENTORY_ITEM>(i + 1));

		//Include only items that have an amount > 0 or are a menu item
		if (items[i].amount > 0 || (items[i].amount == 0 && !item_template.single_use)) {
			decompressed_items.emplace_back(Listbox::Item{
				item_template.name,
				item_template.tooltip,
				item_template.callback_tooltip,
				item_template.callback_fail_tooltip,
				item_template.single_use,
				items[i].amount,
				item_template.callback
			});
		}
	}

	return decompressed_items;
}

Player *savegame::create(u_int8_t save_id) {
	Point start_position = Point(22, 12);

	map::load_section(map::MapSections::GRASSLAND);
	camera::init(start_position);
	sidemenu::init(save_id);
	inventory::init();
	game_objects::init();

	return new Player(Player::MovementDirection::DOWN);
}

void savegame::save(uint8_t save_id) {
	//Check if current save is a new save game and therefore update save_count
	if (options::save_count < save_id) {
		options::save_count = save_id;
		options::save();
	}

	//Fetch item and stargate data
	//TODO handle item compression and decompression in inventory namespace in get_items and load
	std::vector<Listbox::Item> items = inventory::get_items();

	//Save and compress data which will be saved
	auto game_data = GameData{
		map::get_section(),
		camera::get_player_position(),
		Player::get_direction(),
		game_objects::get_saves(),
		compress_items(items)
	};

	write_save(game_data, save_id);
}

Player *savegame::load(uint8_t save_id) {
	Player *player;
	GameData save_data;

	bool save_found = read_save(save_data, save_id);

	//Load data from save game
	if (save_found) {
		//Load position and direction
		map::load_section(save_data.map_section);
		camera::init(save_data.camera_position);
		player = new Player(save_data.player_direction);

		//Init sidemenu
		sidemenu::init(save_id);

		//Load inventory
		inventory::init();
		inventory::load(decompress_items(save_data.items));

		//Load game object states
		game_objects::init();
		game_objects::load_saves(save_data.game_objects);
	} else {
		//If loading save was not successful, create new save
		player = create(save_id);
	}

	return player;
}
