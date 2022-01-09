//
// Created by daniel on 23.09.21.
//

#pragma once

#include "../../../engine/ui/listbox.hpp"
#include "../../../utils/saves/save_types.hpp"

namespace game::inventory {
	void init();

	/**
	 * Loads the compressed items from an array save game to the item vector of the inventory
	 * @param items The compressed item array from the save game
	 */
	void load_save(std::array<save::Item, MAX_ITEMS> &items);

	/**
	* Parses the item vector into an array, because vector cannot be saved directly
	* @param items The item vector to be compressed
	* @return The compressed item array
	*/
	std::array<save::Item, MAX_ITEMS> get_save();

	void cleanup();
	void open();
	void close();
	bool is_open();
	bool add_item(Listbox::Item item);
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
