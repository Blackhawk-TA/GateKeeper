//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

Listbox::Item listbox_item::create_quit_entry() {
	return Listbox::Item{
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
