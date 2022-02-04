//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../utils.hpp"
#include "../../scenes/game/game_objects/player.hpp"
#include "../../items/items.hpp"
#include "../../scenes/game/game_objects/handler/game_object_handler.hpp"
#include "../movement_direction.hpp"

namespace savegame {
	const uint8_t VERSION = 0;

	/**
	 * Create a new save game
	 * @param save_id The id of the save
	 * @return The player instance of the game scene
	 */
	game::Player *create(uint8_t save_id);

	/**
	 * Save the data of a game to a save file
	 * @param save_id The id of the save
	 * @param tmp_save Whether the save is a temporary save for e.g. combat scene transitions
	 */
	void save(uint8_t save_id, bool tmp_save = false);

	/**
	 * Load existing save from file
	 * @param save_id The id of the save
	 * @return The player instance of the game scene
	 */
	game::Player *load(uint8_t save_id, SaveOptions options);

	/**
	 * Gets an array of all game objects of a map section depending on the save id
	 * @param save_id The id of the save
	 * @return array of game objects
	 */
	std::array<game::GameObject::Save, MAX_GAME_OBJECTS> load_game_objects(uint8_t save_id);
}
