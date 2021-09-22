//
// Created by daniel on 21.09.21.
//

#include <iostream>
#include "sidemenu.hpp"
#include "overlay.hpp"
#include "listbox.hpp"

Listbox *menu;
std::vector<Listbox::Item> items;

void sidemenu::init() {
	items = {
			Listbox::Item{
					"ITEMS",
					"Press A to show items",
					"Press B to go back",
					[] {
						std::cout << "ITEMS" << std::endl; //TODO implement
					}
			},
			Listbox::Item{
					"SHOW FPS",
					"Press A to toggle the fps counter",
					"",
					[] {
						overlay::show_fps = !overlay::show_fps;
					}
			},
			Listbox::Item{
					"SAVE",
					"Press A to save the game",
					"Successfully saved!",
					[] {
						std::cout << "SAVE" << std::endl; //TODO implement
					}
			},
			Listbox::Item{
					"EXIT",
					"Press A to exit the menu",
					"",
					[] {
						delete menu;
						menu = nullptr;
					}
			}
	};
}

void sidemenu::open() {
	menu = new Listbox(Rect(16, 0, 4, 6), items);
}

void sidemenu::close() {
	delete menu;
	menu = nullptr;
}

bool sidemenu::is_open() {
	return menu != nullptr;
}

void sidemenu::draw() {
	menu->draw();
}

void sidemenu::cursor_up() {
	menu->cursor_up();
}

void sidemenu::cursor_down() {
	menu->cursor_down();
}

void sidemenu::cursor_press() {
	menu->cursor_press();
}
