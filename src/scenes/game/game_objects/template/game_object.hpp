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
	 * A struct consisting of the data which is stored for each game object
	 */
	struct Data {
		bool player_usable{};
		bool inventory_usable{};
		uint32_t value{};
	};

	/**
	 * A struct consisting of the save signature and data
	 */
	struct Save {
		Signature signature;
		Data data;
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
		SalesmanType = 6,
		VillagerType = 7
	};

	explicit GameObject(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable);
	virtual ~GameObject() = default;

	/**
	 * Gets the signature of an object to clearly identify it.
	 * @return The signature struct of the game object consisting of the map_section and position
	 */
	Signature get_signature();

	/**
	 * Gets the savable struct of a game object to restore the game object data identify the corresponding object on load_save.
	 * @return The savable struct of an object
	 */
	Save get_save();

	/**
	 * Loads the saved state of the game object
	 * @param value The value that is loaded in the game object
	 */
	virtual void load_save(Data data);

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
	 * Checks if the object is currently rendered
	 * @return True, if the object is currently being rendered, else false
	 */
	bool is_rendered();

	/**
	 * Called when the player interacts with a game object
	 * @return True, if interaction successful, else false
	 */
	virtual bool player_interact();

	/**
	 * Called when the player interacts with a game object using the inventory
	 * @return True, if interaction successful, else false
	 */
	virtual bool inventory_interact();

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
	bool player_usable; //Shows if a player can directly interact with it
	bool inventory_usable; //Shows if a player can interact with it using the inventory
	uint32_t value;
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
	 * Sets the player_usable variable for direct player interaction of a game object
	 * @param usable The value showing if the game object is usable by a player directly
	 */
	virtual void set_player_usable(bool usable);

	/**
	 * Sets the inventory_usable variable for player interaction using the inventory of a game object
	 * @param usable The value showing if the game object is usable by a player using the inventory
	 */
	virtual void set_inventory_usable(bool usable);

	/**
	 * Set the additional integer value in which data can be saved for the game object (e.g. timer data for fruit grow)
	 * @param new_value The new integer value to which it should be set
	 */
	virtual void set_value(uint32_t new_value);
};
