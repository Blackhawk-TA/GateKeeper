//
// Created by daniel on 17.09.21.
//

#include "stargate.hpp"
#include "../../../../engine/camera.hpp"

namespace game {
	Stargate::Stargate(map::MapSection map_section, Point position, StargateAddress address, StargateAddress destination, bool inventory_usable)
		: GameObject(map_section, position, false, inventory_usable) {
		Stargate::address = address;
		Stargate::destination = destination;
		activation_start_time = 0;
		size = GATE_SIZE;
		Stargate::set_inventory_usable(inventory_usable);
	}

	bool Stargate::check_collision(Point next_position) {
		return next_position != position + RELATIVE_PRE_ENTRY_POINT &&
		       next_position != position + RELATIVE_ENTRY_POINT &&
		       position.x <= next_position.x && position.y <= next_position.y &&
		       position.x > next_position.x - GATE_SIZE.w && position.y > next_position.y - GATE_SIZE.h;
	}

	void Stargate::update_state(Point next_position) {
		if (state == INACTIVE && (next_position == position + RELATIVE_ACTIVATION_POINT || next_position == position + RELATIVE_PRE_ENTRY_POINT)) {
			set_state(ACTIVATING);
		} else if (state == ACTIVE && next_position != position + RELATIVE_ACTIVATION_POINT && next_position != position + RELATIVE_PRE_ENTRY_POINT) {
			set_state(DEACTIVATING);
		}
	}

	/**
	 * Checks if a player enters the gate, if the gate is on the same map section
	 * @param next_position The next position of the player
	 * @return True if the gate is active and the player enters it, else false
	 */
	bool Stargate::check_enter(Point next_position) {
		return map::get_section() == map_section
			&& state == ACTIVE
			&& next_position == position + RELATIVE_ENTRY_POINT;
	}

	/**
	 * Checks if gate is de-/activating and sets the gate to in-/active once the animation is complete
	 */
	void Stargate::update(uint32_t time) {
		if (state == ACTIVATING || state == DEACTIVATING) {
			if (activation_start_time == 0) {
				activation_start_time = blit::now();
			} else if (blit::now() - activation_start_time >= ANIMATION_DURATION) {
				state == ACTIVATING ? set_state(ACTIVE) : set_state(INACTIVE);
				activation_start_time = 0;
			}
		}
	}

	void Stargate::draw() {
		Point camera_position = camera::get_screen_position();

		//Draw stargate
		screen.blit_sprite(
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				GATE_SIZE.w * TILE_SIZE,
				GATE_SIZE.h * TILE_SIZE
			),
			world_to_screen(position) - camera_position,
			SpriteTransform::NONE
		);

		//Draw animation
		if (state == ACTIVATING || state == DEACTIVATING) {
			screen.blit_sprite(
				Rect(
					(ANIMATION_ID & (spritesheet_size.w - 1)) * TILE_SIZE,
					(ANIMATION_ID / spritesheet_size.h) * TILE_SIZE,
					ANIMATION_SIZE.w * TILE_SIZE,
					ANIMATION_SIZE.h * TILE_SIZE
				),
				world_to_screen(position + ANIMATION_OFFSET) - camera_position, //Calculate animation offset because it's smaller than the gate
				SpriteTransform::NONE
			);
		}
	}

	void Stargate::set_state(uint8_t new_state) {
		auto new_state_enum = static_cast<RenderStates>(new_state);

		switch (new_state_enum) {
			case BROKEN:
				tile_id = tile_id_broken;
				break;
			case INACTIVE:
			case ACTIVATING:
			case DEACTIVATING:
				tile_id = tile_id_inactive;
				break;
			case ACTIVE:
				tile_id = tile_id_active;
				break;
		}

		state = new_state_enum;
	}

	/**
	 * Repairs a broken stargate
	 * @param item_type The listbox_item enum value of the item
	 * @return True, if stargate could be repaired, else false
	 */
	bool Stargate::inventory_interact(listbox_item::INVENTORY_ITEM item_type) {
		if (inventory_usable && item_type == listbox_item::GATE_PART && get_entry_point() == camera::get_player_position()) {
			inventory_usable = false;
			set_state(ACTIVATING);
			return true;
		}

		return false;
	}

	void Stargate::set_inventory_usable(bool usable) {
		Point player_position = camera::get_player_position();
		inventory_usable = usable;
		if (inventory_usable) {
			set_state(BROKEN);
		} else if (player_position == position + RELATIVE_ACTIVATION_POINT || player_position == position + RELATIVE_PRE_ENTRY_POINT) {
			set_state(ACTIVE);
		} else {
			set_state(INACTIVE);
		}
	}

	/**
	 * Get the position at which the player leaves/enters a portal
	 * @return The entry point position
	 */
	Point Stargate::get_entry_point() {
		return position + RELATIVE_PRE_ENTRY_POINT;
	}

	/**
	 * Gets the destination gate to which this gate is linked
	 * @return The destination gate
	 */
	StargateAddress Stargate::get_destination() {
		return destination;
	}

	/**
	 * Gets the address of the stargate
	 * @return The address of the stargate
	 */
	StargateAddress Stargate::get_address() {
		return address;
	}

	/**
	 * Gets the map section on which the gate is located
	 * @return The map section of the gate
	 */
	map::MapSection Stargate::get_map_section() {
		return map_section;
	}

	GameObject::ObjectType Stargate::get_type() {
		return StargateType;
	}
}
