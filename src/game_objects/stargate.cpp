//
// Created by daniel on 17.09.21.
//

#include "stargate.hpp"
#include "../engine/camera.hpp"

//TODO add collision
Stargate::Stargate(Point position, Point destination, bool broken) {
	Stargate::position = position;
	Stargate::destination = destination;
	sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);
	screen_tiles = get_screen_tiles();
	activation_start_time = 0;

	//TODO load stored data if it was repaired
	if (!broken) { //TODO remove negation
		set_state(BROKEN);
	} else {
		set_state(INACTIVE);
	}
}

//TODO handle all checks within handler/class and only call one function within player movement function
bool Stargate::check_collision(Point next_position) const {
	return next_position != position + RELATIVE_PRE_ENTRY_POINT &&
		position.x <= next_position.x && position.y <= next_position.y &&
		position.x > next_position.x - GATE_SIZE.x && position.y > next_position.y - GATE_SIZE.y;
}

void Stargate::check_activation(Point next_position) {
	if (state == INACTIVE && (next_position == position + RELATIVE_ACTIVATION_POINT || next_position == position + RELATIVE_PRE_ENTRY_POINT)) {
		set_state(ACTIVATING);
	} else if (state == ACTIVE && next_position != position + RELATIVE_ACTIVATION_POINT && next_position != position + RELATIVE_PRE_ENTRY_POINT) {
		set_state(DEACTIVATING);
	}
}

bool Stargate::check_enter(Point next_position) {
	return state == ACTIVE && next_position == position + RELATIVE_ENTRY_POINT;
}

Point Stargate::get_destination() {
	return destination;
}

void Stargate::update_animation() {
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
