//
// Created by D069765 on 26.10.2021.
//

#include "gate_statue.hpp"
#include "../engine/camera.hpp"
#include "../ui/inventory.hpp"
#include "../items/items.hpp"

GateStatue::GateStatue(map::MapSections map_section, Point position, bool usable) : GameObject(map_section, position, usable) {
	size = Size(1, 3);
	GateStatue::set_usable(usable);
}

bool GateStatue::interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (camera::get_player_position() == position + Point(0, size.h) && usable) {
		set_usable(false);
		inventory::add_item(listbox_item::create_inventory_item(listbox_item::GATE_PART));
		return true;
	}

	return false;
}

void GateStatue::update_state(Point next_position) {
	if (map::get_section() != map_section) {
		return;
	}

	//Show as active when player stands directly in front of the statue
	if (state == INACTIVE && next_position == position + Point(0, size.h)) {
		set_state(ACTIVE);
	} else if (state == ACTIVE) {
		set_state(INACTIVE);
	}
}

void GateStatue::set_state(uint8_t new_state) {
	auto new_state_enum = static_cast<RenderStates>(new_state);

	switch (new_state_enum) {
		case DEPLETED:
			tile_id = TILE_ID_EMPTY;
			break;
		case INACTIVE:
			tile_id = TILE_ID_INACTIVE;
			break;
		case ACTIVE:
			tile_id = TILE_ID_ACTIVE;
			break;
	}

	state = new_state_enum;
}

void GateStatue::set_usable(bool value) {
	usable = value;

	if (value) {
		set_state(INACTIVE);
	} else {
		set_state(DEPLETED);
	}

	update_state(camera::get_player_position());
}
