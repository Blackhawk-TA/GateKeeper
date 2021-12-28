//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../utils.hpp"
#include "../../scenes/game/player.hpp"
#include "../../items/items.hpp"
#include "../../scenes/game/handlers/game_objects/game_object_handler.hpp"

namespace savegame {
	const uint8_t VERSION = 0;
	struct Item {
		uint8_t type;
		uint8_t amount;
	};

	struct GameData {
		uint8_t version;
		map::MapSections map_section;
		Point camera_position;
		game::Player::MovementDirection player_direction;
		uint8_t player_health;
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects;
		std::array<Item, MAX_ITEMS> items;
		uint32_t passed_time;
	};

	game::Player *create(uint8_t save_id);
	void save(uint8_t save_id);
	game::Player *load(uint8_t save_id);
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> load_game_objects(uint8_t save_id);
}
