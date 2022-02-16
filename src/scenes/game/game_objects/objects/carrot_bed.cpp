//
// Created by daniel on 07.11.21.
//

#include "carrot_bed.hpp"
#include "../../../../utils/game_time.hpp"
#include "../../ui/sidemenu.hpp"

namespace game {
	CarrotBed::CarrotBed(map::MapSection map_section, Point position) : GameObject(map_section, position, false, false) {
		size = Size(1, 1);
		value = game_time::get_time() + GROW_STAGE_1_TIME + GROW_STAGE_2_TIME; //Value equals grow time
		CarrotBed::set_state(PLANTED);
		CarrotBed::set_player_usable(player_usable);
		CarrotBed::set_inventory_usable(inventory_usable);
	}

	void CarrotBed::update(uint32_t time) {
		if (state != GROWN && state != HARVESTED) {
			if (value < game_time::get_time()) {
				set_player_usable(true);
			} else if (state != GROWING && value - GROW_STAGE_1_TIME < game_time::get_time()) {
				set_state(GROWING);
			} else if (state != PLANTED && state != GROWING && value - GROW_STAGE_1_TIME - GROW_STAGE_2_TIME < game_time::get_time()) {
				set_state(PLANTED);
			}
		}
	}

	bool CarrotBed::player_interact() {
		if (player_usable && in_range()) {
			bool has_inventory_space = sidemenu::add_item(sidemenu::INVENTORY, items::create_inventory_item(items::INVENTORY_ITEM::CARROT));
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

	bool CarrotBed::inventory_interact(items::INVENTORY_ITEM item_type) {
		if (inventory_usable && item_type == items::CARROT_SEED && in_range()) {
			value = game_time::get_time() + GROW_STAGE_1_TIME + GROW_STAGE_2_TIME;
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

	void CarrotBed::update_state(Point next_position) {}
}
