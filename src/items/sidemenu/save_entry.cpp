//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../utils/savegame.hpp"

Listbox::Item inventory_item::create_save_entry(uint8_t save_id) {
	return Listbox::Item{
		"SAVE",
		"Press A to save the game.",
		"Successfully saved!",
		"Could not save the game.",
		false,
		0,
		[save_id] {
			savegame::save(save_id);
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
