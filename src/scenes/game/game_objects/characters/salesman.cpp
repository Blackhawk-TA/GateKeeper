//
// Created by daniel on 24.11.21.
//

#include "salesman.hpp"
#include "../../../../engine/camera.hpp"

Salesman::Salesman(map::MapSections map_section, Point position) : Character(map_section, position, true, false) {
	tile_id = TILE_ID;
}

GameObject::ObjectType Salesman::get_type() {
	return SalesmanType;
}

bool Salesman::player_interact() {
	if (player_usable && camera::get_player_position() == position + Point(0, size.h + BAR_HEIGHT)) {
		textbox = new Textbox("Test message");
		return true;
	}

	return false;
}

void Salesman::update_state(Point next_position) {}
void Salesman::set_state(uint8_t new_state) {}
void Salesman::update(uint32_t time) {}
