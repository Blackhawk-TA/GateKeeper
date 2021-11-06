//
// Created by daniel on 06.11.21.
//

#include "sign.hpp"
#include "../../../engine/camera.hpp"

Sign::Sign(map::MapSections map_section, Point position, Sign::SpriteType sprite_type, std::string text) : GameObject(map_section, position, true) {
	Sign::text = std::move(text);
	set_sprite(sprite_type);
}

bool Sign::interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (camera::get_player_position() == position + Point(0, size.h) && usable) {
		textbox = new Textbox(text);
		return true;
	}

	return false;
}

void Sign::set_sprite(Sign::SpriteType sprite_type) {
	switch (sprite_type) {
		case STONE:
			tile_id = 173;
			size = Size(1, 2);
			break;
		case WOOD:
			tile_id = 451;
			size = Size(1, 1);
			break;
	}
}

GameObject::ObjectType Sign::get_type() {
	return SignType;
}

void Sign::set_state(uint8_t new_state) {}
void Sign::update_state(Point next_position) {}
void Sign::set_usable(bool value) {}
void Sign::update(uint32_t time) {}
