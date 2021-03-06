//
// Created by daniel on 06.11.21.
//

#include "sign.hpp"
#include "../../../../engine/camera.hpp"

namespace game {
	Sign::Sign(map::MapSection map_section, Point position, Sign::SpriteType sprite_type, std::string text)
		: GameObject(map_section, position, true, false) {
		Sign::text = std::move(text);
		set_sprite(sprite_type);
	}

	bool Sign::player_interact() {
		if (player_usable && player_in_front()) {
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
}
