//
// Created by daniel on 06.11.21.
//

#include "sign.hpp"
#include "../../../../engine/camera.hpp"

namespace game {
	Sign::Sign(map::MapSections map_section, Point position, Sign::SpriteType sprite_type, std::string text)
		: GameObject(map_section, position, true, false) {
		Sign::text = std::move(text);
		set_sprite(sprite_type);
	}

	bool Sign::player_interact() {
		if (player_usable && camera::get_player_position() == position + Point(0, size.h)) {
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

	void Sign::update(uint32_t time) {}
}
