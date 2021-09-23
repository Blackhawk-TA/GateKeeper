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
			[] {
				inventory::open();
				sidemenu::close();
			}
		},
		Listbox::Item{
			"SHOW FPS",
			"Press A to toggle the fps counter.",
			"",
			[] {
				overlay::show_fps = !overlay::show_fps;
			}
		},
		Listbox::Item{
			"SAVE",
			"Press A to save the game.",
			"Successfully saved!",
			[] {
				std::cout << "SAVE" << std::endl; //TODO implement
			}
		},
		Listbox::Item{
			"EXIT",
			"Press A to exit the menu.",
			"",
			[] {
				sidemenu::close();
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
