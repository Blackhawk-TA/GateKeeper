//
// Created by daniel on 22.09.21.
//

#include "listbox.hpp"

Listbox::Listbox(Rect rect, std::vector<Item> &items) : Box(rect) {
	Listbox::rect = rect;
	Listbox::items = items;
	spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	cursor_position = Point(rect.x, rect.y + CURSOR_OFFSET);
	tooltip = new Textbox("");
	update_tooltip();
}

Listbox::~Listbox() {
	delete tooltip;
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

/**
 * Handles a press on a listbox item
 * @return The index of the pressed listbox item
 */
void Listbox::cursor_press() {
	uint8_t item_index = cursor_position.y - rect.y - CURSOR_OFFSET;

	if (!items.empty() && item_index < items.size()) {
		std::string callback_tooltip = items[item_index].callback_tooltip;
		std::string callback_fail_tooltip = items[item_index].callback_fail_tooltip;
		Tooltip tooltip_state = items[item_index].callback();

		switch (tooltip_state) {
			case SUCCESS:
				tooltip->set_text(callback_tooltip);
				break;
			case FAILURE:
				tooltip->set_text(callback_fail_tooltip);
				break;
			case SUPPRESS:
				break;
		}

		//Delete items that can only be used once
		if (tooltip_state == Tooltip::SUCCESS && items[item_index].single_use) {
			remove_item(item_index);
		}
	}
}

void Listbox::update_tooltip() {
	uint8_t item_index = cursor_position.y - rect.y - CURSOR_OFFSET;
	if (!items.empty() && item_index < items.size()) {
		tooltip->set_text(items[item_index].tooltip);
	}
}

void Listbox::remove_item(uint8_t index) {
	auto it = items.begin();
	bool found = false;
	uint8_t counter = 0;

	while (!found && it != items.end()) {
		if (counter == index) {
			it = items.erase(it);
			found = true;
		} else {
			it++;
			counter++;
		}
	}
}
