//
// Created by daniel on 21.09.21.
//

#include "box.hpp"

Box::Box(Rect rect) {
	Box::rect = rect;
	Box::visible = true;
	spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
}

void Box::draw() const {
	if (visible) {
		uint8_t x, y;
		uint16_t sprite_id;
		for (x = 0u; x < rect.w; x++) {
			for (y = 0u; y < rect.h; y++) {
				if (x == 0 && y == 0) {
					sprite_id = sprite_id_top_left;
				} else if (x == rect.w - 1 && y == rect.h - 1) {
					sprite_id = sprite_id_bottom_right;
				} else if (x == rect.w - 1 && y == 0) {
					sprite_id = sprite_id_top_right;
				} else if (x == 0 && y == rect.h - 1) {
					sprite_id = sprite_id_bottom_left;
				} else if (x == 0 && y < rect.h - 1) {
					sprite_id = sprite_id_center_left;
				} else if (x == rect.w - 1 && y < rect.h - 1) {
					sprite_id = sprite_id_center_right;
				} else if (y == 0) {
					sprite_id = sprite_id_top_center;
				} else if (y == rect.h - 1) {
					sprite_id = sprite_id_bottom_center;
				} else {
					sprite_id = sprite_id_center_center;
				}

				screen.blit_sprite(
						Rect(
								(sprite_id & (spritesheet_size.w - 1)) * TILE_SIZE,
								(sprite_id / spritesheet_size.h) * TILE_SIZE,
								TILE_SIZE,
								TILE_SIZE
						),
						Point((rect.x + x) * TILE_SIZE, (rect.y + y) * TILE_SIZE),
						SpriteTransform::NONE
				);
			}
		}
	}
}

void Box::set_visibility(bool value) {
	visible = value;
}
