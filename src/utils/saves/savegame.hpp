//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../utils.hpp"
#include "../../scenes/game/characters/player.hpp"
#include "../../items/items.hpp"
#include "../../scenes/game/handlers/game_objects/game_object_handler.hpp"

namespace savegame {
	struct Item {
		uint8_t type;
		uint8_t amount;
	};

	struct GameData {
		map::MapSections map_section;
		Point camera_position;
		Player::MovementDirection player_direction;
		uint8_t player_health;
		std::array<GameObject::Save, game_objects::GAME_OBJECT_COUNT> game_objects;
		std::array<Item, listbox_item::INVENTORY_COUNTER> items;
		uint32_t passed_time;
	};

	Player *create(uint8_t save_id);
	void save(uint8_t save_id);
	Player *load(uint8_t save_id);
}
