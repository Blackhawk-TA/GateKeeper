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

	game::Player *create(uint8_t save_id);
	void save(uint8_t save_id, bool tmp_save = false);
	game::Player *load(uint8_t save_id, SaveOptions options);
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> load_game_objects(uint8_t save_id);
}
