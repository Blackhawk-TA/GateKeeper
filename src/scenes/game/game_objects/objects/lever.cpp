//
// Created by daniel on 19.12.21.
//

#include "lever.hpp"
#include "../../../../engine/camera.hpp"

Lever::Lever(map::MapSections map_section, Point position, bool working) : GameObject(map_section, position, true, false) {
	tile_id = TILE_ID_OFF;
	size = Size(1, 1);
	Lever::working = working;
	Lever::set_state(OFF);
}

bool Lever::player_interact() {
	if (player_usable && camera::get_player_position() == position + Point(0, size.h)) {
		if (state == ON) {
			textbox = new Textbox("The lever is already set to on.");
			return true;
		}

		if (working) {
			textbox = new Textbox("Sounds like a door opened.");
			//TODO open door
		} else {
			textbox = new Textbox("Nothing happens.");
		}

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
