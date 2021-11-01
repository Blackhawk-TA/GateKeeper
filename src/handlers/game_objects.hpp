//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "../game_objects/game_object_interface.hpp"
#include "../engine/map.hpp"

//TODO think about integrating stargate into a gameobject, might not make sense since a gate is special due to the objects being linked
namespace game_objects {
	/**
	 * The amount of game objects on the map
	 */
	constexpr uint16_t GAME_OBJECT_COUNT = 1;

	/**
	 * Creates the objects using their factory function
	 */
	void init();

	/**
	 * Deletes all objects from memory
	 */
	void cleanup();

	/**
	 * Gets array with save structs of all game objects objects
	 */
	std::array<IGameObject::Save, GAME_OBJECT_COUNT> get_saves();

	/**
	 * Loads saved objects into each game object
	 * @param saved_objects The saved game objects pointer array
	 */
	void load_saves(std::array<IGameObject::Save, GAME_OBJECT_COUNT> &saved_objects);

	/**
	 * Draws all game objects
	 */
	void draw();

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
