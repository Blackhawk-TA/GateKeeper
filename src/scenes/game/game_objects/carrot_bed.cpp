//
// Created by daniel on 07.11.21.
//

#include "carrot_bed.hpp"
#include "../../../utils/game_time.hpp"
#include "../../../engine/camera.hpp"
#include "../../../items/items.hpp"
#include "../ui/inventory.hpp"

//TODO use integer save value to save time, also use value for time in FruitTrees
CarrotBed::CarrotBed(map::MapSections map_section, Point position) : GameObject(map_section, position, false, false) {
	size = Size(1, 1);
	grown_time = game_time::get_time() + (PLANT_TIME_MS + GROWING_TIME_MS + GROWN_TIME_MS) / 2;
	CarrotBed::set_state(PLANTED);
	CarrotBed::set_player_usable(player_usable);
	CarrotBed::set_inventory_usable(inventory_usable);
}

void CarrotBed::update(uint32_t time) {
	if (map::get_section() != map_section) {
		return;
	}

	//TODO grow rate seems off
	if (state != GROWN && state != HARVESTED) {
		if (grown_time < game_time::get_time()) {
			set_player_usable(true);
		} else if (state != GROWING && grown_time - (GROWING_TIME_MS + PLANT_TIME_MS) < game_time::get_time()) {
			set_state(GROWING);
		} else if (state != PLANTED && grown_time - (GROWN_TIME_MS *GROWING_TIME_MS + PLANT_TIME_MS) < game_time::get_time()) {
			set_state(PLANTED);
		}
	}
}

bool CarrotBed::player_interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (player_usable && in_use_range()) {
		bool has_inventory_space = inventory::add_item(listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::CARROT));
		if (has_inventory_space) {
			set_player_usable(false);
			set_inventory_usable(true);
			textbox = new Textbox("You put a carrot in your inventory.");
		} else {
			textbox = new Textbox("You cannot carry any more carrots.");
		}
		return true;
	} else {
		return false;
	}
}

bool CarrotBed::inventory_interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (inventory_usable && in_use_range()) {
		grown_time = game_time::get_time() + (PLANT_TIME_MS + GROWING_TIME_MS + GROWN_TIME_MS);
		set_inventory_usable(false);
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
	} else {
		set_state(HARVESTED);
	}
}

void CarrotBed::set_inventory_usable(bool usable) {
	inventory_usable = usable;

	if (inventory_usable) {
		set_state(HARVESTED);
	} else {
		set_state(PLANTED);
	}
}

bool CarrotBed::in_use_range() {
	return camera::get_player_position() == position + Point(0, size.h)
		|| camera::get_player_position() == position - Point(0, size.h)
		|| camera::get_player_position() == position + Point(size.w, 0)
		|| camera::get_player_position() == position - Point(size.w, 0);
}

void CarrotBed::update_state(Point next_position) {}
