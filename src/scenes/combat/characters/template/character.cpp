//
// Created by daniel on 26.12.21.
//

#include "character.hpp"
#include "../../../../engine/camera.hpp"

namespace combat {
	Character::Character(Point position) {
		Character::position = position;

		tile_id = 0;
		screen_position = world_to_screen(position);
		spritesheet_size = get_spritesheet_size(screen.bounds);
	}

	void Character::draw() {
		screen.blit(
			player_sprites,
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				SIZE.w * TILE_SIZE,
				SIZE.h * TILE_SIZE
			),
			screen_position - camera::get_screen_position(),
			SpriteTransform::NONE
		);
	}
}