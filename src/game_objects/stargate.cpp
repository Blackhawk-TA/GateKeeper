//
// Created by daniel on 17.09.21.
//

#include "stargate.hpp"
#include "../engine/camera.hpp"

//TODO add collision
Stargate::Stargate(Point position, bool broken) {
	Stargate::position = position;
	sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);
	screen_tiles = get_screen_tiles();

	state = broken ? BROKEN : INACTIVE;
	tile_id = get_tile_id(state);
}

void Stargate::draw() {
	Point camera_position_world = screen_to_world(camera::get_screen_position());

	if (camera_position_world.x < position.x + gate_size.x && camera_position_world.y < position.y + gate_size.y &&
	screen_tiles.x + camera_position_world.x - position.x > 0 && screen_tiles.y + camera_position_world.y - position.y > 0)
	{
		screen.blit_sprite(
				Rect(
						(tile_id & (sprite_sheet_size.x - 1)) * TILE_SIZE,
						(tile_id / sprite_sheet_size.y) * TILE_SIZE,
						gate_size.x * TILE_SIZE,
						gate_size.y * TILE_SIZE
				),
				world_to_screen(position) - camera::get_screen_position(),
				SpriteTransform::NONE
		);
	}
}

//TODO maybe include in set_state
uint16_t Stargate::get_tile_id(Stargate::RenderStates current_state) {
	uint16_t id = 0;

	switch (current_state) {
		case BROKEN:
			id = 1763;
			break;
		case INACTIVE:
			id = 683;
			break;
		case ACTIVE:
			id = 872;
			break;
	}

	return id;
}

void Stargate::set_state(Stargate::RenderStates new_state) {
	tile_id = get_tile_id(new_state);
}
