//
// Created by D069765 on 11.01.2022.
//

#include "../items.hpp"
#include "../../utils/saves/options.hpp"
#include "../../utils/saves/save_types.hpp"

Listbox::Item listbox_item::create_reset_all_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"RESET ALL",
		"Reset all save data of the game",
		"Successfully deleted all save data",
		"",
		false,
		0,
		[] {
			//TODO properly delete data
			write_save(0, 0);
			for (uint8_t i = 0u; i < options::MAX_SAVES; i++) {
				write_save(save::SaveData{}, i + 1);
			}
			write_save(save::SaveData{}, TMP_SAVE_ID);

			return Listbox::Tooltip::SUCCESS;
		},
		true
	};
}
