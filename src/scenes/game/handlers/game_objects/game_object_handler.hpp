//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "../../game_objects/template/game_object.hpp"
#include "../../../../engine/map.hpp"

namespace game_objects {
	/**
	 * The amount of game objects on the map
	 */
	constexpr uint16_t GAME_OBJECT_COUNT = 7;

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
	 * Draws all game objects
	 */
	void draw();

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
	 * Checks if there was an interaction with a game object and trigger interaction
	 * @return True, if interaction successful, else false
	 */
	bool interact();

	/**
	 * Updates the states of the objects when a player moves closer to it
	 * @param next_position The next position of the player
	 */
	void update_states(Point next_position);
}
