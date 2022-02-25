//
// Created by daniel on 25.10.21.
//

#pragma once
#include "../../../../utils/utils.hpp"
#include "../../../../engine/map.hpp"
#include "../../../../engine/ui/textbox.hpp"
#include "../../../../items/items.hpp"

namespace game {
	class GameObject {
	public:
		/**
		 * A struct consisting of the data which is stored for each game object
		 */
		struct Data {
			bool player_usable{};
			bool inventory_usable{};
			bool is_active{};
			uint32_t value{};
		};

		/**
		 * A struct consisting of the save signature and data
		 */
		struct Save {
			Signature signature{};
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
			CharacterType = 6,
			LeverType = 7,
			DungeonDoorType = 8,
			CrystalType = 9,
			EnemyType = 10,
		};

		explicit GameObject(map::MapSection map_section, Point position, bool player_usable, bool inventory_usable, bool draw_under_player = true);
		virtual ~GameObject();

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
		 * Draws the textbox separately to ensure it is rendered on top of all game objects
		 */
		void draw_textbox();

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
		 * Shows the next textbox if the text is too long for one.
		 * @return True if the next textbox is shown, else false
		 */
		bool next_textbox();

		/**
		 * Closes the textbox of the game object
		 */
		virtual void close_textbox();

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
		 * @param item_type The listbox_item enum value of the item
		 * @return True, if interaction successful, else false
		 */
		virtual bool inventory_interact(items::INVENTORY_ITEM item_type);

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

		/**
		 * Get if the game object should be drawn under or over the players' sprite
		 * @return True if the game object should be drawn under the player's sprite
		 */
		bool is_drawn_under_player() const;

		/**
		 * Checks if the player is looking at the game object and standing within the interaction distance
		 * @param distance The amount of tiles that exists between the player and game object for an interaction to be possible
		 * @return True if the player is in front of the game object, else false
		 */
		bool in_range(uint8_t distance = 0);

		/**
		 * Checks if the player is in front of the game object. This means he is looking up and the game object is above him
		 * @param distance The amount of tiles that exists between the player and game object for an interaction to be possible
		 * @return True if the player is in front of the game object, else false
		 */
		bool player_in_front(uint8_t distance = 0);

		/**
		 * Sets the game object active state. Inactive game objects are not rendered nor accessible.
		 * They still exist in memory and their states are therefore saved.
		 * @param active The boolean showing if a game object is active
		 */
		virtual void set_active(bool active);

	protected:
		Point position;
		map::MapSection map_section;
		bool player_usable; //Shows if a player can directly interact with it
		bool inventory_usable; //Shows if a player can interact with it using the inventory
		bool draw_under_player; //Shows if the game object should be drawn under the player sprite
		bool is_active;
		uint32_t value;
		Signature signature;
		Size spritesheet_size;
		uint16_t tile_id;
		Size size;
		Textbox *textbox;

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
}
