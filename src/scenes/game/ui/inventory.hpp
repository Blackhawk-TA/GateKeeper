//
// Created by daniel on 24.01.22.
//

#pragma once
#include "../../../engine/ui/listbox.hpp"
#include "../../../utils/saves/save_types.hpp"

namespace game::ui {
	class Inventory : public Listbox {
		~Inventory() override = default;

	public:
		explicit Inventory(Rect rect, std::vector<Item> &items);

		/**
		 * Loads the compressed items from an array save game to the item vector of the inventory
		 * @param items The compressed item array from the save game
		 */
		void load_save(std::array<save::Item, ::MAX_ITEMS> &save_items);

		/**
		* Parses the item vector into an array, because vector cannot be saved directly
		* @param items The item vector to be compressed
		* @return The compressed item array
		*/
		std::array<save::Item, ::MAX_ITEMS> get_save();
	};
}
