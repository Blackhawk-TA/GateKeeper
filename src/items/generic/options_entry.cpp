//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"

Listbox::Item items::create_options_entry(uint8_t type_id, uint8_t save_id) {
	return Listbox::Item{
		type_id,
		"OPTIONS",
		"Press A to go to the options",
		"",
		"",
		false,
		0,
		[save_id] {
			SceneOptions options = {
				save_id
			};
			load_scene(SceneType::OPTIONS, options);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
