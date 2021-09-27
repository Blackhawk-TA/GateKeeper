//
// Created by daniel on 26.09.21.
//

#include "../items.hpp"
#include "../../ui/overlay.hpp"

Listbox::Item inventory_item::create_show_fps_entry() {
	return Listbox::Item{
		"SHOW FPS",
		"Press A to toggle the fps counter.",
		"Toggled fps counter.",
		"",
		false,
		0,
		[] {
			overlay::show_fps = !overlay::show_fps;
			return Listbox::Tooltip::SUCCESS;
		}
	};
}
