//
// Created by daniel on 19.12.21.
//

#include "lever.hpp"
#include "../handler/extensions/dungeon_door_handler.hpp"

namespace game {
	Lever::Lever(map::MapSection map_section, Point position, Signature interaction_object, bool working) : GameObject(map_section, position, true, false) {
		tile_id = TILE_ID_OFF;
		size = Size(1, 1);
		Lever::working = working;
		Lever::interaction_object = interaction_object;
		Lever::set_state(OFF);
	}

	bool Lever::player_interact() {
		if (player_usable && player_in_front()) {
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
				value = 1;
				break;
			case OFF:
				tile_id = TILE_ID_OFF;
				value = 0;
				break;
		}

		state = new_state_enum;
	}

	void Lever::set_value(uint32_t new_value) {
		GameObject::set_value(new_value);

		if (new_value == 1) {
			set_state(ON);
		} else {
			set_state(OFF);
		}
	}
}
