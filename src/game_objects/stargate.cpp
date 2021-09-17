//
// Created by daniel on 17.09.21.
//

#include "stargate.hpp"

//TODO make camera a namespace, add camera position to gate position
Stargate::Stargate(Point position, bool broken) {
	Stargate::position = position;
	sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);

	state = broken ? BROKEN : INACTIVE;
	tile_id = get_tile_id(state);
}

void Stargate::draw() {
	screen.blit_sprite( //TODO only render when in screen
		Rect((tile_id & (sprite_sheet_size.x - 1)) * TILE_SIZE, (tile_id / sprite_sheet_size.y) * TILE_SIZE, tile_size, tile_size),
		world_to_screen(position),
		SpriteTransform::NONE
	);
}

//TODO maybe change back to set state
uint16_t Stargate::get_tile_id(Stargate::RenderStates new_state) {
	uint16_t id = 0;

	switch (new_state) {
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
