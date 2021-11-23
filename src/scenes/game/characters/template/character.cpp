//
// Created by daniel on 01.11.21.
//
#include "character.hpp"
#include "../../../../engine/camera.hpp"

Character::Character(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable) {
	Character::position = position;
	Character::map_section = map_section;
	Character::player_usable = player_usable;
	Character::inventory_usable = inventory_usable;
	Character::spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	Character::textbox = nullptr;

	//Generate object signature
	signature = Signature{
		map_section,
		position
	};
}

void Character::draw() {
	screen.blit_sprite(
		Rect(
			(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
			(tile_id / spritesheet_size.h) * TILE_SIZE,
			TILE_SIZE,
			TILE_SIZE
		),
		world_to_screen(position) - camera::get_screen_position(),
		SpriteTransform::NONE
	);

	//Draw textbox notification
	if (textbox != nullptr) {
		textbox->draw();
	}
}

bool Character::is_textbox_open() {
	return textbox != nullptr;
}

void Character::close_textbox() {
	delete textbox;
	textbox = nullptr;
}

bool Character::check_collision(Point next_position) {
	return position.x <= next_position.x && position.y <= next_position.y &&
	       position.x > next_position.x && position.y > next_position.y;
}

Character::Signature Character::get_signature() {
	return signature;
}

Character::Save Character::get_save() {
	return Save{
		signature,
		Data{
			player_usable,
			inventory_usable,
			value
		}
	};
}

void Character::load_save(Data data) {
	set_player_usable(data.player_usable);
	set_inventory_usable(data.inventory_usable);
	set_value(data.value);
}

void Character::set_player_usable(bool usable) {
	player_usable = usable;
}

void Character::set_inventory_usable(bool usable) {
	inventory_usable = usable;
}

void Character::set_value(uint32_t new_value) {
	value = new_value;
}

bool Character::player_interact() {
	return false;
}

bool Character::inventory_interact() {
	return false;
}

bool Character::is_rendered() {
	return map::get_section() == map_section
		&& sprite_rect_in_screen(position, Size(1, 1), camera::get_world_position());
}
