//
// Created by daniel on 24.11.21.
//

#include "salesman.hpp"

namespace game {
	Salesman::Salesman(map::MapSection map_section, Point position) : Character(map_section, position, true, false) {
		tile_id = TILE_ID;
		set_movement_sprites();
	}

	bool Salesman::player_interact() {
		if (player_usable && player_in_front(BAR_HEIGHT)) {
			textbox = new Textbox("Hello! Normally I would sell you carrot seeds but they are all gone.");
			return true;
		}

		return false;
	}
}
