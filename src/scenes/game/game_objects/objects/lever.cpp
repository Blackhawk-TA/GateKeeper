//
// Created by daniel on 19.12.21.
//

#include "lever.hpp"
#include "../../../../engine/camera.hpp"
#include "../../handlers/game_objects/extensions/dungeon_door_handler.hpp"

namespace game {
	Lever::Lever(map::MapSection map_section, Point position, Signature interaction_object, bool working) : GameObject(map_section, position, true, false) {
		tile_id = TILE_ID_OFF;
		size = Size(1, 1);
		Lever::working = working;
		Lever::interaction_object = interaction_object;
		Lever::set_state(OFF);
	}

	bool Lever::player_interact() {
		if (player_usable && camera::get_player_position() == position + Point(0, size.h)) {
			if (state == ON) {
				textbox = new Textbox("The lever is already set to on.");
				return true;
			}

			std::string text;
			if (working) {
				if (dungeon_door_handler::open_door(interaction_object)) {
					text = "Sounds like a door opened.";
				} else {
					text = "Nothing happens, but it should have worked...";
				}
			} else {
				text = "Nothing happens.";
			}

			textbox = new Textbox(text);
			set_state(ON);
			return true;
		}

		return false;
	}

	GameObject::ObjectType Lever::get_type() {
		return LeverType;
	}

	void Lever::set_state(uint8_t new_state) {
		auto new_state_enum = static_cast<State>(new_state);

		switch (new_state_enum) {
			case ON:
				tile_id = TILE_ID_ON;
				break;
			case OFF:
				tile_id = TILE_ID_OFF;
				break;
		}

		state = new_state_enum;
	}

	void Lever::update(uint32_t time) {}

	void Lever::update_state(Point next_position) {}
}
