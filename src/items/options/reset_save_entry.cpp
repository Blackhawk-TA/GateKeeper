//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"

Listbox::Item listbox_item::create_reset_save_entry(uint8_t type_id, uint8_t save_id) {
	return Listbox::Item{
		type_id,
		"RESET " + std::to_string(save_id),
		"Delete the saved game on slot " + std::to_string(save_id),
		"Successfully deleted save " + std::to_string(save_id),
		"",
		false,
		0,
		[save_id] {
			write_save("", save_id);
			//TODO updates saves counter, should not be able to delete save from within the game
			return Listbox::Tooltip::SUCCESS;
		},
		true
	};
}
