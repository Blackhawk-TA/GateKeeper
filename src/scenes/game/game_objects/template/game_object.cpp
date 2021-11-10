//
// Created by daniel on 01.11.21.
//
#include "game_object.hpp"
#include "../../../../engine/camera.hpp"

GameObject::GameObject(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable) {
	GameObject::position = position;
	GameObject::map_section = map_section;
	GameObject::player_usable = player_usable;
	GameObject::inventory_usable = inventory_usable;
	GameObject::spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	GameObject::textbox = nullptr;

	//Generate object signature
	signature = Signature{
		map_section,
		position
	};
}

void GameObject::draw() {
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
	return position.x <= next_position.x && position.y <= next_position.y &&
	       position.x > next_position.x - size.w && position.y > next_position.y - size.h;
}

GameObject::Signature GameObject::get_signature() {
	return signature;
}

GameObject::Save GameObject::get_save() {
	return Save{
		signature,
		Data{
			player_usable,
			inventory_usable,
			value
		}
	};
}

void GameObject::load_save(Data data) {
	set_player_usable(data.player_usable);
	set_inventory_usable(data.inventory_usable);
	set_value(data.value);
}

void GameObject::set_player_usable(bool usable) {
	player_usable = usable;
}

void GameObject::set_inventory_usable(bool usable) {
	inventory_usable = usable;
}

void GameObject::set_value(uint32_t new_value) {
	value = new_value;
}

bool GameObject::player_interact() {
	return false;
}

bool GameObject::inventory_interact() {
	return false;
}

bool GameObject::on_active_map_section() {
	return map::get_section() == map_section;
}
