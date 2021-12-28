//
// Created by D069765 on 26.10.2021.
//

#include "gate_statue.hpp"
#include "../../../../engine/camera.hpp"
#include "../../ui/inventory.hpp"

namespace game {
	GateStatue::GateStatue(map::MapSections map_section, Point position, bool player_usable)
	: GameObject(map_section, position, player_usable, false) {
		size = Size(1, 3);
		GateStatue::set_player_usable(player_usable);
	}

	bool GateStatue::player_interact() {
		if (player_usable && camera::get_player_position() == position + Point(0, size.h)) {
			bool has_inventory_space = inventory::add_item(listbox_item::create_inventory_item(listbox_item::GATE_PART));
			if (has_inventory_space) {
				set_player_usable(false);
				textbox = new Textbox("You picked up a Gate Part!");
			} else {
				textbox = new Textbox("You cannot carry any more Gate Parts.");
			}
			return true;
		}

		return false;
	}

	void GateStatue::update_state(Point next_position) {
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

	void GateStatue::set_player_usable(bool usable) {
		player_usable = usable;

		if (usable) {
			set_state(INACTIVE);
		} else {
			set_state(DEPLETED);
		}

		update_state(camera::get_player_position());
	}

	GameObject::ObjectType GateStatue::get_type() {
		return GateStatueType;
	}

	void GateStatue::update(uint32_t time) {}
}
