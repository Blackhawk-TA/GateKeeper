//
// Created by daniel on 21.09.21.
//

#include "box.hpp"

Box::Box(Rect rect) {
	Box::rect = set_bounds(rect);
	Box::visible = true;
	spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
}

/**
 * Checks if the rectangle is fully visible on the screen and adjusts its size if necessary.
 * @param r The rectangle of the box
 * @return The rectangle which fits the screen.
 */
Rect Box::set_bounds(Rect &r) {
	Point screen_tiles = get_screen_tiles();

	//Check width
	if (r.w > screen_tiles.x) {
		r.w = screen_tiles.x;
	}

	//Check height
	if (r.h > screen_tiles.y) {
		r.h = screen_tiles.y;
	}

	//Check x position + width
	if (r.x + r.w > screen_tiles.x) {
		r.x = screen_tiles.x - r.w;
	}

	//Check y position + height
	if (r.y + r.h > screen_tiles.y) {
		r.y = screen_tiles.y - r.h;
	}

	return {r.x, r.y, r.w, r.h};
}

void Box::draw() {
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
					continue; //Don't draw the centerpieces for better performance
				}

				screen.blit(
					screen.sprites,
					Rect(
						(sprite_id & (spritesheet_size.w - 1)) * TILE_SIZE,
						(sprite_id / spritesheet_size.h) * TILE_SIZE,
						TILE_SIZE,
						TILE_SIZE
					),
					Point((rect.x + x) * TILE_SIZE, (rect.y + y) * TILE_SIZE)
				);
			}
		}

		//Draw the centerpieces as white rectangle
		screen.pen = Pen(255, 255, 255, 255);
		screen.rectangle(Rect(
			rect.x * TILE_SIZE + TILE_SIZE,
			rect.y * TILE_SIZE + TILE_SIZE,
			rect.w * TILE_SIZE - 2 * TILE_SIZE,
			rect.h * TILE_SIZE - 2 * TILE_SIZE)
		);
	}
}

void Box::set_visibility(bool value) {
	visible = value;
}

bool Box::is_visible() const {
	return visible;
}
