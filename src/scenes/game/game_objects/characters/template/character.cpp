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

bool Character::player_interact() {
	bool interacted = false;

	if (player_usable) {
		if (camera::get_player_position() == position + Point(0, size.h)) {
			interacted = true;
			change_direction(DOWN, false);
		} else if (camera::get_player_position() == position - Point(0, size.h)) {
			interacted = true;
			change_direction(UP, false);
		} else if (camera::get_player_position() == position + Point(size.w, 0)) {
			interacted = true;
			change_direction(RIGHT, false);
		} else if (camera::get_player_position() == position - Point(size.w, 0)) {
			interacted = true;
			change_direction(LEFT, false);
		}
	}

	return interacted;
}

void Character::change_direction(MovementDirection direction, bool animate) {
	if (current_direction != direction) {
		animation_sprites = movement_sprites.at(direction);
		current_direction = direction;
		tile_id = animate ? animation_sprites[1] : animation_sprites[0]; //Set sprite manually to avoid timer delay on player turn
	}
}
