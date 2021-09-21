//
// Created by daniel on 21.09.21.
//

#include <iostream>
#include "sidemenu.hpp"
#include "overlay.hpp"

bool sidemenu::visible = false;

const uint16_t cursor_sprite_id = 1742;
const uint8_t list_count = 4;
std::array<std::string, list_count> list;
Size spritesheet_size;
Box *menu;
Point cursor_position;

//TODO cleanup and remove magic numbers, maybe add tooltips
void sidemenu::init() {
	spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	menu = new Box(Rect(16, 0, 4, 6));
	cursor_position = Point(16, 1);
	list = {
		"ITEMS",
		"SHOW FPS",
		"SAVE",
		"EXIT"
	};
}

void sidemenu::draw() {
	menu->draw();
	screen.pen = Pen(0, 0, 0, 255);

	for (uint8_t i = 0; i < list_count; i++) {
		screen.text(list[i], minimal_font, Rect(17 * TILE_SIZE, (i + 1) * TILE_SIZE + 5, TILE_SIZE * 3, TILE_SIZE));
	}

	screen.blit_sprite(
			Rect(
					(cursor_sprite_id & (spritesheet_size.w - 1)) * TILE_SIZE,
					(cursor_sprite_id / spritesheet_size.h) * TILE_SIZE,
					TILE_SIZE,
					TILE_SIZE
			),
			world_to_screen(cursor_position),
			SpriteTransform::NONE
	);
}

void sidemenu::cursor_up() {
	if (cursor_position.y > 1) {
		cursor_position.y--;
	}
}

void sidemenu::cursor_down() {
	if (cursor_position.y < list_count) {
		cursor_position.y++;
	}
}

void sidemenu::press() {
	switch (cursor_position.y) {
		case 1: //ITEMS
			std::cout << "ITEMS" << std::endl;
			break;
		case 2: //SHOW FPS
			overlay::show_fps = !overlay::show_fps;
			break;
		case 3: //SAVE
			std::cout << "SAVE" << std::endl;
			break;
		case 4: //EXIT
			visible = false;
			break;
	}
}
