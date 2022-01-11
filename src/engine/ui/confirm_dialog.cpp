//
// Created by D069765 on 11.01.2022.
//

#include "confirm_dialog.hpp"

ConfirmDialog::ConfirmDialog(Rect rect) : Box(rect) {
	ConfirmDialog::rect = rect;
	cursor_position = Point(rect.x, rect.y);
	visible = false;
}

void ConfirmDialog::draw() {
	if (!visible) return;

	Box::draw();

	//Draw cursor
	screen.blit_sprite(
		Rect(
			(CURSOR_SPRITE_ID & (spritesheet_size.w - 1)) * TILE_SIZE,
			(CURSOR_SPRITE_ID / spritesheet_size.h) * TILE_SIZE,
			TILE_SIZE,
			TILE_SIZE
		),
		world_to_screen(cursor_position) + Point(0, HALF_PADDING_PX),
		SpriteTransform::NONE
	);

	for (uint8_t i = 0u; i < confirm_options.size(); i++) {
		screen.text(
			confirm_options[i],
			FONT,
			Rect(
				(rect.x + PADDING) * TILE_SIZE,
				static_cast<int>(rect.y + i) * TILE_SIZE + HALF_PADDING_PX + FONT.char_h / 2,
				rect.w * TILE_SIZE,
				TILE_SIZE
			)
		);
	}
}

void ConfirmDialog::cursor_reset() {
	cursor_position = Point(rect.x, rect.y);
}

void ConfirmDialog::cursor_up() {
	if (cursor_position.y - rect.y > 0) {
		cursor_position.y--;
	}
}

void ConfirmDialog::cursor_down() {
	if (cursor_position.y - rect.y < static_cast<int>(confirm_options.size()) - 1) {
		cursor_position.y++;
	}
}

void ConfirmDialog::cursor_press(const std::function<void()>& callback) {
	uint8_t item_index = cursor_position.y - rect.y;

	if (item_index == 0) {
		callback();
	}

	visible = false;
	cursor_reset();
}
