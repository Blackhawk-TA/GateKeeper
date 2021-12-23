//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "../../game_objects/template/game_object.hpp"
#include "../../../../engine/map.hpp"
#include "../../../../items/items.hpp"

namespace game_objects {
	/**
	 * The amount of game objects on the map
	 */
	constexpr uint16_t GAME_OBJECT_COUNT = 25;

	/**
	 * Creates the objects using their factory function
	 */
	void init();

	/**
	 * Gets the game object collection
	 * @return The game object collection
	 */
	std::vector<GameObject*> &get_collection();

	/**
	 * Deletes all objects from memory
	 */
	void cleanup();

	/**
	 * Gets array with save structs of all game objects objects
	 */
	std::array<GameObject::Save, GAME_OBJECT_COUNT> get_saves();

	/**
	 * Loads saved objects into each game object
	 * @param saved_objects The saved game objects pointer array
	 */
	void load_saves(std::array<GameObject::Save, GAME_OBJECT_COUNT> &saved_objects);

	/**
	 * Draws the game objects which should be rendered under the player
	 */
	void drawUnderPlayer();

	/**
	 * Draws the game objects which should be rendered over the player
	 */
	void drawOverPlayer();

	/**
	 * Updates all game objects
	 */
	void update(uint32_t time);

	/**
	 * Checks if a game object has an open textbox
	 * @return True, if there is a textbox open, else false
	 */
	bool is_textbox_open();

	/**
	 * Closes all textboxes opened by game objects
	 */
	void close_textboxes();

	/**
	 * Check if a game object collides with the player's next position
	 * @param next_position The next position of the player
	 * @return True if a collision happened, else false
	 */
	bool check_collisions(Point next_position);

	/**
	 * Checks if there was a player interaction with a game object and triggers interaction
	 * @return True, if interaction successful, else false
	 */
	bool player_interact();

	/**
	 * Checks if there was a player interaction with a game object using the inventory and triggers interaction
	 * @param item_type The listbox_item enum value of the item
	 * @return True, if interaction successful, else false
	 */
	bool inventory_interact(listbox_item::INVENTORY_ITEM item_type);

	/**
	 * Updates the states of the objects when a player moves closer to it
	 * @param next_position The next position of the player
	 */
	void update_states(Point next_position);

	/**
	 * Compares the signatures of two game object and checks if they are equal
	 * @param sig1 The signature of the first game object
	 * @param sig2 The signature of the second game object
	 * @return True if the signatures are equal, else false
	 */
	bool has_equal_signature(GameObject::Signature sig1, GameObject::Signature sig2);
}
