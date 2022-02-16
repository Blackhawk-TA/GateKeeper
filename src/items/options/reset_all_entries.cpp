//
// Created by D069765 on 11.01.2022.
//

#include "../items.hpp"
#include "../../utils/saves/options.hpp"

Listbox::Item items::create_reset_all_entries(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"RESET ALL",
		"Reset all save data of the game",
		"Successfully deleted all save data",
		"",
		false,
		0,
		[] {
			remove_save(0);
			for (uint8_t i = 0u; i < options::MAX_SAVES; i++) {
				remove_save(i + 1);
			}
			remove_save(TMP_SAVE_ID);

			load_previous_scene();
			return Listbox::Tooltip::SUCCESS;
		},
		true
	};
}
