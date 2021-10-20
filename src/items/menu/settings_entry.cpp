//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

Listbox::Item listbox_item::create_settings_entry() {
	return Listbox::Item{
		"SETTINGS",
		"Press A to go to the settings",
		"",
		"",
		false,
		0,
		[] {
			load_scene(Scene::SETTINGS);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
