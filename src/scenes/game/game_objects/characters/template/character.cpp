//
// Created by daniel on 01.11.21.
//
#include "character.hpp"
#include "../../../../../engine/camera.hpp"

Character::Character(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable)
	: GameObject(map_section, position, player_usable, inventory_usable) {
	Character::size = Size(1, 1);
	Character::spritesheet_size = get_spritesheet_size(player_sprites->bounds);
}

void Character::draw() {
	screen.blit(
		player_sprites,
		Rect(
			(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
			(tile_id / spritesheet_size.h) * TILE_SIZE,
			size.w * TILE_SIZE,
			size.h * TILE_SIZE
		),
		world_to_screen(position) - camera::get_screen_position(),
		SpriteTransform::NONE
	);

	//Draw textbox notification
	if (textbox != nullptr) {
		textbox->draw();
	}
}
