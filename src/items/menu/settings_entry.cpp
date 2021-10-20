//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../game.hpp"

Listbox::Item listbox_item::create_options_entry() {
	return Listbox::Item{
		"OPTIONS",
		"Press A to go to the options",
		"",
		"",
		false,
		0,
		[] {
			load_scene(Scene::OPTIONS);
			return Listbox::Tooltip::SUPPRESS;
		}
	};
}
