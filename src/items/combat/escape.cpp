//
// Created by daniel on 30.12.21.
//

#include "../items.hpp"

Listbox::Item listbox_item::create_combat_escape(uint8_t type_id, uint8_t save_id) {
	return Listbox::Item{
		type_id,
		"ESCAPE",
		"Tries to escape from the fight.",
		"Escaped!",
		"Could not escape!",
		false,
		0,
		[save_id] {
			if (blit::random() % 3 == 0) {
				SceneOptions options = {
					save_id,
					{},
					true,
					true
				};
				load_scene(SceneType::GAME, options);
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
