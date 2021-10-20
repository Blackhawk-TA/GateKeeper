//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

Listbox::Item listbox_item::create_settings_exit_entry() {
	return Listbox::Item{
		"EXIT",
		"Press A to go to the menu.",
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
