//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../utils.hpp"
#include "../../scenes/game/player.hpp"
#include "../../items/items.hpp"
#include "../../scenes/game/handlers/game_objects/game_object_handler.hpp"
#include "../movement_direction.hpp"

namespace savegame {
	const uint8_t VERSION = 0;
	struct Item {
		uint8_t type;
		uint8_t amount;
	};

	struct GameData { //TODO when changed after release, create GameDataV1 struct to allow porting the saves
		uint8_t version;
		map::MapSection map_section;
		Point camera_position;
		Point previous_camera_position;
		MovementDirection player_direction;
		uint8_t player_health;
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects; //TODO this causes save warning
		std::array<Item, MAX_ITEMS> items;
		uint32_t passed_time;
	};

	game::Player *create(uint8_t save_id);
	void save(uint8_t save_id, bool tmp_save = false);
	game::Player *load(uint8_t save_id, bool tmp_save = false, bool previous_player_position = false);
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> load_game_objects(uint8_t save_id);
}
