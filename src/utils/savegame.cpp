//
// Created by daniel on 24.09.21.
//

#include "savegame.hpp"
#include "../ui/inventory.hpp"
#include "../ui/overlay.hpp"

/**
 * Parses the item vector into an array, because vector cannot be saved directly
 * @param items The item vector to be compressed
 * @return The compressed item array
 */
 //TODO not working when item amount is 0, maybe create own struct for menu items, it cant differ
std::array<savegame::Item, inventory_item::INVENTORY_ITEM::INVENTORY_COUNTER> compress_items(std::vector<Listbox::Item> &items) {
	std::array<savegame::Item, inventory_item::INVENTORY_ITEM::INVENTORY_COUNTER> compressed_items = {};

	for (auto i = 0u; i < items.size(); i++) {
		if (items[i].amount > 0) {
			compressed_items[i] = savegame::Item{
				static_cast<inventory_item::INVENTORY_ITEM>(i),
				items[i].amount
			};
		}
	}

	return compressed_items;
}

std::vector<Listbox::Item> decompress_items(std::array<savegame::Item, inventory_item::INVENTORY_COUNTER> &items) {
	std::vector<Listbox::Item> decompressed_items = {};
	Listbox::Item item_template;

	for (auto i = 0u; i < items.size(); i++) {
		item_template = inventory_item::create_inventory_item(static_cast<inventory_item::INVENTORY_ITEM>(i));

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

/**
 * Parses the stargates map into an array containing only the broken boolean. The compressed index mirrors the gate address
 * @param stargates The stargate map to be compressed
 * @return The compressed stargate array
 */
std::array<bool, StargateAddresses::COUNTER> compress_gates(std::map<StargateAddresses, Stargate> &stargates) {
	std::array<bool, StargateAddresses::COUNTER> compressed_gates = {};

	for (auto &stargate: stargates) {
		compressed_gates[stargate.first] = stargate.second.is_broken();
	}

	return compressed_gates;
}

std::map<StargateAddresses, Stargate> decompress_gates(std::array<bool, StargateAddresses::COUNTER> &stargates) {
	std::map<StargateAddresses, Stargate> decompressed_gates = stargate_handler::get_stargates();

	for (auto &decompressed_gate: decompressed_gates) {
		for (auto i = 0u; i < stargates.size(); i++) {
			if (decompressed_gate.first == i) {
				decompressed_gate.second.set_broken(stargates[i]);
			}
		}
	}

	return decompressed_gates;
}

Player *savegame::create() {
	Point start_position = Point(22, 12);

	camera::init(start_position);
	stargate_handler::init();
	inventory::init();

	return new Player(Player::MovementDirection::DOWN);
}

void savegame::save() {
	//Fetch item and stargate data
	std::vector<Listbox::Item> items = inventory::get_items();
	std::map<StargateAddresses, Stargate> stargates = stargate_handler::get_stargates();

	//Save and compress data which will be saved
	auto game_data = GameData{
		overlay::show_fps,
		map::get_section(),
		camera::get_player_position(),
		Player::get_direction(),
		compress_items(items),
		compress_gates(stargates)
	};

	write_save(game_data);
}

Player *savegame::load() {
	Player *player;
	GameData save_data;

	bool save_found = read_save(save_data);

	//Load data from save game
	if (save_found) {
		//Load fps setting
		overlay::show_fps = save_data.show_fps;

		//Load position and direction
		map::load_section(save_data.map_section);
		camera::init(save_data.camera_position);
		player = new Player(save_data.player_direction);

		//Load inventory
		inventory::load(decompress_items(save_data.items));

		//Initialize stargates to set their broken state later
		stargate_handler::init();

		//Load broken state of stargates
		stargate_handler::load(decompress_gates(save_data.gate_states));
	} else {
		//If loading save was not successful, create new save
		player = create();
	}

	return player;
}
