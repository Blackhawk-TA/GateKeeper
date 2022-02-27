//
// Created by daniel on 24.11.21.
//

#include "salesman.hpp"
#include "../../../../utils/game_time.hpp"
#include "../../ui/sidemenu.hpp"

namespace game {
	Salesman::Salesman(map::MapSection map_section, Point position) : Character(map_section, position, true, false) {
		tile_id = TILE_ID;
		value = game_time::get_time() + COOLDOWN_MS; //Value equals cooldown for item handout
		set_movement_sprites();
	}

	bool Salesman::player_interact() {
		if (player_usable && player_in_front(BAR_HEIGHT)) {
			if (value < game_time::get_time()) {
				value = game_time::get_time() + COOLDOWN_MS;
				textbox = new Textbox("Hello! You look hungry. Unfortunately I don't have any food here but I can give you a few carrot seeds. Just plant them and you'll have something to eat soon.");
				sidemenu::add_item(sidemenu::INVENTORY, items::create_inventory_item(items::CARROT_SEED), 6);
			} else {
				textbox = new Textbox("Oh, I already gave you all my carrot seeds. If you come back later I might have some for you. I expect a new delivery of carrot seeds soon.");
			}
			return true;
		}

		return false;
	}
}
