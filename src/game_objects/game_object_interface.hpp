//
// Created by daniel on 25.10.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "../engine/map.hpp"

class IGameObject {
public:
	/**
	 * A struct consisting of the map_section and position of a game object to create a unique signature.
	 */
	struct Signature {
		map::MapSections map_section;
		Point position;
	};

	/**
	 * A struct of the savable value of a game object including the signature.
	 */
	struct Save {
		Signature signature;
		bool value{};
	};

	virtual ~IGameObject() = default;

	/**
	 * Gets the signature of an object to clearly identify it.
	 * @return The signature struct of the game object consisting of the map_section and position
	 */
	virtual Signature get_signature() = 0;

	/**
	 * Gets the savable struct of a game object to store a bool value and identify the corresponding object on load_save.
	 * @return The savable struct of an object
	 */
	virtual Save get_save() = 0;

	/**
	 * Loads the saved state of the game object
	 * @param value The value that is loaded in the game object
	 */
	virtual void load_save(bool value) = 0;

	/**
	 * Checks if the game object collides with the player's next position
	 * @param next_position The next position of the player
	 * @return True, if a collision takes place, else false
	 */
	virtual bool check_collision(Point next_position) = 0;

	/**
	 * Draws the game object
	 */
	virtual void draw() = 0;

	/**
	 * Called when the player interacts with a game object
	 * @return True, if interaction successful, else false
	 */
	virtual bool interact() = 0;

	/**
	 * Updates the state of the object when a player moves closer to it
	 * @param next_position The next position of the player
	 */
	virtual void update_state(Point next_position) = 0;

protected:
	/**
	 * Sets the state and tile_id of the object
	 * @param new_state The new render state
	 */
	virtual void set_state(uint8_t new_state) = 0;

	/**
	 * Sets the usable variable of a game object and updates the state
	 * @param value The value showing if the game object is usable by a player
	 */
	virtual void set_usable(bool value) = 0;
};
