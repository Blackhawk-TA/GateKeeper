//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

Listbox::Item listbox_item::create_quit_entry(uint8_t type_id) {
	return Listbox::Item{
		type_id,
		"QUIT",
		"Press A to go back to the menu and save.",
		"",
		"",
		false,
		0,
		[] {
			load_scene(Scene::MENU);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
