//
// Created by daniel on 21.09.21.
//

#include <iostream>
#include "sidemenu.hpp"
#include "overlay.hpp"
#include "controls/listbox.hpp"
#include "inventory.hpp"

void sidemenu::init() {
	control = nullptr;
	items = {
		Listbox::Item{
			"ITEMS",
			"Press A to show items, press B to return to menu.",
			"",
			"",
			false,
			0,
			[] {
				inventory::open();
				sidemenu::close();
				return Listbox::Tooltip::SUPPRESS;
			}
		},
		Listbox::Item{
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
		},
		Listbox::Item{
			"SAVE",
			"Press A to save the game.",
			"Successfully saved!",
			"Could not save the game.",
			false,
			0,
			[] {
				std::cout << "SAVE" << std::endl; //TODO implement
				return Listbox::Tooltip::SUCCESS;
			}
		},
		Listbox::Item{
			"EXIT",
			"Press A to exit the menu.",
			"",
			"",
			false,
			0,
			[] {
				sidemenu::close();
				return Listbox::Tooltip::SUPPRESS;
			}
		}
	};
}

void sidemenu::open() {
	control = new Listbox(Rect(16, 0, 4, 6), items);
}

void sidemenu::close() {
	delete control;
	control = nullptr;
}

bool sidemenu::is_open() {
	return control != nullptr;
}

void sidemenu::draw() {
	control->draw();
}

void sidemenu::cursor_up() {
	control->cursor_up();
}

void sidemenu::cursor_down() {
	control->cursor_down();
}

void sidemenu::cursor_press() {
	control->cursor_press();
}
