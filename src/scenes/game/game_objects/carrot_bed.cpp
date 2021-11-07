//
// Created by daniel on 07.11.21.
//

#include "carrot_bed.hpp"
#include "../../../utils/game_time.hpp"
#include "../../../engine/camera.hpp"
#include "../../../items/items.hpp"
#include "../ui/inventory.hpp"

CarrotBed::CarrotBed(map::MapSections map_section, Point position, bool usable) : GameObject(map_section, position, usable) {
	size = Size(1, 1);
	grown_time = game_time::get_time() + (PLANT_TIME_MS + GROWING_TIME_MS + GROWN_TIME_MS) / 2;
	set_state(PLANTED);
	CarrotBed::set_player_usable(usable);
}

void CarrotBed::update(uint32_t time) {
	if (map::get_section() != map_section) {
		return;
	}

	if (!player_usable && state != HARVESTED) {
		if (state != GROWN && grown_time < game_time::get_time()) {
			set_player_usable(true);
		} else if (state != GROWING && grown_time - (GROWING_TIME_MS + PLANT_TIME_MS) < game_time::get_time()) {
			set_state(GROWING);
		} else if (state != PLANTED && grown_time - (GROWN_TIME_MS *GROWING_TIME_MS + PLANT_TIME_MS) < game_time::get_time()) { //TODO fix
			set_state(PLANTED);
		}
	}
}

bool CarrotBed::interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (player_usable && in_use_range()) {
		bool has_inventory_space = inventory::add_item(listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::CARROT));
		if (has_inventory_space) {
			set_player_usable(false);
			textbox = new Textbox("You put a carrot in your inventory.");
		} else {
			textbox = new Textbox("You cannot carry any more carrots.");
		}
		return true;
	} else {
		return false;
	}
}

GameObject::ObjectType CarrotBed::get_type() {
	return CarrotBedType;
}

void CarrotBed::set_state(uint8_t new_state) {
	auto new_state_enum = static_cast<RenderStates>(new_state);

	switch (new_state_enum) {
		case HARVESTED:
			tile_id = TILE_ID_HARVESTED;
			break;
		case PLANTED:
			tile_id = TILE_ID_PLANTED;
			break;
		case GROWING:
			tile_id = TILE_ID_GROWING;
			break;
		case GROWN:
			tile_id = TILE_ID_GROWN;
			break;
	}

	state = new_state_enum;
}

void CarrotBed::set_player_usable(bool usable) {
	player_usable = usable;

	if (player_usable) {
		set_state(GROWN);
	} else if (state == GROWN) {
		set_state(HARVESTED);
	} else {
		set_state(PLANTED); //TODO with "inventory usable" flag in GameObject check, also add this flag to saves
	}
}

bool CarrotBed::plant() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (state == HARVESTED &&  in_use_range()) {
		grown_time = game_time::get_time() + (PLANT_TIME_MS + GROWING_TIME_MS + GROWN_TIME_MS);
		set_state(PLANTED);
		return true;
	} else {
		return false;
	}
}

bool CarrotBed::in_use_range() {
	return camera::get_player_position() == position + Point(0, size.h)
		|| camera::get_player_position() == position - Point(0, size.h)
		|| camera::get_player_position() == position + Point(size.w, 0)
		|| camera::get_player_position() == position - Point(size.w, 0);
}

void CarrotBed::update_state(Point next_position) {}
