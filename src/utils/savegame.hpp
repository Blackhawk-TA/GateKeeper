//
// Created by daniel on 24.09.21.
//

#pragma once
#include "utils.hpp"
#include "../ui/controls/listbox.hpp"
#include "../player.hpp"
#include "../items/items.hpp"

namespace savegame {
	struct Item {
		inventory_item::INVENTORY_ITEM type;
		uint8_t amount;
	};

	struct GameData {
		bool show_fps;
		map::MapSections map_section;
		Point camera_position;
		Player::MovementDirection player_direction;
		std::array<Item, inventory_item::INVENTORY_COUNTER> items;
		std::array<bool, StargateAddresses::COUNTER> gate_states;
	};

	Player *create();
	void save();
	Player *initial_load();
}
