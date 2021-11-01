//
// Created by daniel on 01.11.21.
//
#include "game_object.hpp"
#include "../../../../engine/camera.hpp"

GameObject::GameObject(map::MapSections map_section, Point position, bool usable) {
	GameObject::position = position;
	GameObject::map_section = map_section;
	GameObject::usable = usable;
	GameObject::spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	GameObject::textbox = nullptr;

	//Generate object signature
	signature = Signature{
		map_section,
		position
	};
}

void GameObject::draw() {
	if (map::get_section() != map_section) {
		return;
	}

	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	if (sprite_rect_in_screen(position, size, camera_position_world)) {
		screen.blit_sprite(
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				size.w * TILE_SIZE,
				size.h * TILE_SIZE
			),
			world_to_screen(position) - camera_position,
			SpriteTransform::NONE
		);
	}

	//Draw textbox notification
	if (textbox != nullptr) {
		textbox->draw();
	}
}

bool GameObject::is_textbox_open() {
	return textbox != nullptr;
}

void GameObject::close_textbox() {
	delete textbox;
	textbox = nullptr;
}

bool GameObject::check_collision(Point next_position) {
	if (map::get_section() != map_section) {
		return false;
	}

	return position.x <= next_position.x && position.y <= next_position.y &&
	       position.x > next_position.x - size.w && position.y > next_position.y - size.h;
}

GameObject::Signature GameObject::get_signature() {
	return signature;
}

GameObject::Save GameObject::get_save() {
	return Save{
		signature,
		usable
	};
}

void GameObject::load_save(bool value) {
	set_usable(value);
}
