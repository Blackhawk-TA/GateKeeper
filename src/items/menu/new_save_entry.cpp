//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"

Listbox::Item items::create_new_save_entry(uint8_t type_id, uint8_t save_id) {
	std::string save_id_str = std::to_string(save_id);

	return Listbox::Item{
		type_id,
		"NEW GAME",
		"Press A to create a new game.",
		"Creating game...",
		"",
		false,
		0,
		[save_id] {
			SceneOptions options = {
				save_id,
			};
			load_scene(SceneType::GAME, options);
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
