//
// Created by daniel on 22.09.21.
//

#include "listbox.hpp"

Listbox::Listbox(Rect rect, std::vector<Item> &items) : Box(rect) {
	Listbox::rect = rect;
	Listbox::items = items;
	Listbox::spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	Listbox::cursor_position = Point(rect.x, rect.y + CURSOR_OFFSET);
	tooltip = new Textbox("");
	update_tooltip();
}

void Listbox::draw() {
	tooltip->draw();
	Box::draw();
	screen.pen = Pen(0, 0, 0, 255);

	if (items.empty()) {
		//Draw no items text
		screen.text(
				"No items",
				font,
				Rect(
						(rect.x + PADDING) * TILE_SIZE,
						static_cast<int>(rect.y + PADDING) * TILE_SIZE + font.char_h / 2,
						rect.w * TILE_SIZE,
						TILE_SIZE
				)
		);
	} else {
		//Draw Item names
		for (auto i = 0u; i < items.size(); i++) {
			screen.text(
					items[i].name,
					font,
					Rect(
							(rect.x + PADDING) * TILE_SIZE,
							static_cast<int>(rect.y + i + PADDING) * TILE_SIZE + font.char_h / 2,
							rect.w * TILE_SIZE,
							TILE_SIZE
					)
			);
		}

		//Draw cursor
		screen.blit_sprite(
			Rect(
						(CURSOR_SPRITE_ID & (spritesheet_size.w - 1)) * TILE_SIZE,
						(CURSOR_SPRITE_ID / spritesheet_size.h) * TILE_SIZE,
						TILE_SIZE,
						TILE_SIZE
				),
				world_to_screen(cursor_position),
				SpriteTransform::NONE
		);
	}
}

void Listbox::cursor_up() {
	if (cursor_position.y - rect.y > 1) {
		cursor_position.y--;
	}

	update_tooltip();
}

void Listbox::cursor_down() {
	if (cursor_position.y - rect.y < static_cast<uint8_t>(items.size())) {
		cursor_position.y++;
	}

	update_tooltip();
}

void Listbox::cursor_press() {
	uint8_t item_index = cursor_position.y - rect.y - CURSOR_OFFSET;
	if (!items.empty() && item_index < items.size()) {
		items[item_index].callback();
		std::string callback_tooltip = items[item_index].callback_tooltip;
		if (!callback_tooltip.empty()) {
			tooltip->set_text(callback_tooltip);
		}
	}
}

void Listbox::update_tooltip() {
	uint8_t item_index = cursor_position.y - rect.y - CURSOR_OFFSET;
	if (!items.empty() && item_index < items.size()) {
		tooltip->set_text(items[item_index].tooltip);
	}
}
