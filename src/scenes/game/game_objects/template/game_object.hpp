//
// Created by daniel on 25.10.21.
//

#pragma once
#include "../../../../utils/utils.hpp"
#include "../../../../engine/map.hpp"
#include "../../../../engine/ui/textbox.hpp"

class GameObject {
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

	/**
	 * Game Object types. Required since PicoSystem does not support Run Time Type Information
	 */
	enum ObjectType {
		GateStatueType = 1,
		StargateType = 2,
		SignType = 3,
		FruitTreeType = 4,
		CarrotBedType = 5,
	};

	explicit GameObject(map::MapSections map_section, Point position, bool usable);
	virtual ~GameObject() = default;

	/**
	 * Gets the signature of an object to clearly identify it.
	 * @return The signature struct of the game object consisting of the map_section and position
	 */
	Signature get_signature();

	/**
	 * Gets the savable struct of a game object to store a bool value and identify the corresponding object on load_save.
	 * @return The savable struct of an object
	 */
	Save get_save();

	/**
	 * Loads the saved state of the game object
	 * @param value The value that is loaded in the game object
	 */
	virtual void load_save(bool value);

	/**
	 * Checks if the game object collides with the player's next position
	 * @param next_position The next position of the player
	 * @return True, if a collision takes place, else false
	 */
	virtual bool check_collision(Point next_position);

	/**
	 * Draws the game object
	 */
	virtual void draw();

	/**
	 * Called on the GameScenes update function
	 */
	virtual void update(uint32_t time) = 0;

	/**
	 * Checks if a textbox created by this game object is open
	 * @return True, if a textbox is open, else false
	 */
	bool is_textbox_open();

	/**
	 * Closes the textbox of the game object
	 */
	void close_textbox();

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

	/**
	 * Gets the type of the game object
	 * @return The game object type
	 */
	virtual ObjectType get_type() = 0;

protected:
	Point position;
	map::MapSections map_section;
	bool usable;
	Signature signature;
	Size spritesheet_size;
	uint16_t tile_id;
	Size size;
	Textbox* textbox;

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
