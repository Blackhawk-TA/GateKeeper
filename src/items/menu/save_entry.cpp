//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../utils/savegame.hpp"

Listbox::Item inventory_item::create_save_entry() {
	return Listbox::Item{
		"SAVE",
		"Press A to save the game.",
		"Successfully saved!",
		"Could not save the game.",
		false,
		0,
		[] {
			savegame::save();
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
