//
// Created by daniel on 17.09.21.
//

#include "stargate.hpp"
#include "../engine/camera.hpp"

Stargate::Stargate(map::MapSections map_section, stargate_handler::Stargates destination, Point position, bool broken) {
	Stargate::map_section = map_section;
	Stargate::position = position;
	Stargate::destination = destination;
	sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);
	screen_tiles = get_screen_tiles();
	activation_start_time = 0;

	//TODO load stored data if it was repaired
	if (broken) {
		set_state(BROKEN);
	} else {
		set_state(INACTIVE);
	}
}

/**
 * Check for player collisions with the gate
 * @param next_position The next position of the player
 * @return True, if a collision took place, else false
 */
bool Stargate::check_collision(Point next_position) const {
	if (map::get_section() != map_section) {
		return false;
	}

	return next_position != position + RELATIVE_PRE_ENTRY_POINT &&
		next_position != position + RELATIVE_ENTRY_POINT &&
		position.x <= next_position.x && position.y <= next_position.y &&
		position.x > next_position.x - GATE_SIZE.x && position.y > next_position.y - GATE_SIZE.y;
}

/**
 * If the gate is on the same map section, change the gate state depending on the next position of the player
 * @param next_position The next position the player
 */
void Stargate::update_state(Point next_position) {
	if (map::get_section() != map_section) {
		return;
	}

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
	if (map::get_section() != map_section) {
		return false;
	}

	return state == ACTIVE && next_position == position + RELATIVE_ENTRY_POINT;
}

/**
 * Checks if gate is de-/activating and sets the gate to in-/active once the animation is complete
 */
void Stargate::update_animation() {
	if (map::get_section() != map_section) {
		return;
	}

	if (state == ACTIVATING || state == DEACTIVATING) {
		if (activation_start_time == 0) {
			activation_start_time = blit::now();
		} else if (blit::now() - activation_start_time >= ANIMATION_DURATION) {
			state == ACTIVATING ? set_state(ACTIVE) : set_state(INACTIVE);
			activation_start_time = 0;
		}
	}
}

/**
 * Draws the gate if it is on the active map section and draws the gate animation if the gate is de-/activating
 */
void Stargate::draw() {
	if (map::get_section() != map_section) {
		return;
	}

	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	if (camera_position_world.x < position.x + GATE_SIZE.x && camera_position_world.y < position.y + GATE_SIZE.y &&
	screen_tiles.x + camera_position_world.x - position.x > 0 && screen_tiles.y + camera_position_world.y - position.y > 0)
	{
		//Draw stargate
		screen.blit_sprite(
				Rect(
						(tile_id & (sprite_sheet_size.x - 1)) * TILE_SIZE,
						(tile_id / sprite_sheet_size.y) * TILE_SIZE,
						GATE_SIZE.x * TILE_SIZE,
						GATE_SIZE.y * TILE_SIZE
				),
				world_to_screen(position) - camera_position,
				SpriteTransform::NONE
		);

		//Draw animation
		if (state == ACTIVATING || state == DEACTIVATING) {
			screen.blit_sprite(
					Rect(
							(ANIMATION_ID & (sprite_sheet_size.x - 1)) * TILE_SIZE,
							(ANIMATION_ID / sprite_sheet_size.y) * TILE_SIZE,
							ANIMATION_SIZE.x * TILE_SIZE,
							ANIMATION_SIZE.y * TILE_SIZE
					),
					world_to_screen(position + GATE_SIZE - ANIMATION_SIZE) -
					camera_position, //Calculate animation offset because it's smaller than the gate
					SpriteTransform::NONE
			);
		}
	}
}

/**
 * Sets the state and tile_id of the gate
 * @param new_state The new state
 */
void Stargate::set_state(Stargate::RenderStates new_state) {
	switch (new_state) {
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

	state = new_state;
}

void Stargate::repair() {
	if (state == BROKEN) { //TODO auto activate if player is in front of portal
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
stargate_handler::Stargates Stargate::get_destination() {
	return destination;
}

/**
 * Gets the map section on which the gate is located
 * @return The map section of the gate
 */
map::MapSections Stargate::get_map_section() {
	return map_section;
}
