//
// Created by daniel on 24.11.21.
//

#include "salesman.hpp"
#include "../../../../utils/game_time.hpp"
#include "../../ui/sidemenu.hpp"

namespace game {
	Salesman::Salesman(map::MapSection map_section, Point position, Supply supply) : Character(map_section, position, true, false) {
		Salesman::supply = supply;

		switch (supply) {
			case ITEMS:
				tile_id = 20;
				message = "Hello! Welcome to my shop. I can sell you food and seeds to plant your own food.";
				break;
			case GEAR:
				tile_id = 140;
				message = "Hello! Welcome to my shop. I can sell you weapons that help you to defend yourself against any enemy.";
				break;
		}

		set_movement_sprites();
	}

	bool Salesman::player_interact() {
		if (player_usable && player_in_front(BAR_HEIGHT)) {
			textbox = new Textbox(message);
			return true;
		}

		return false;
	}

	void Salesman::close_textbox() {
		GameObject::close_textbox();

		switch (supply) {
			case ITEMS:
				sidemenu::open(sidemenu::ITEM_SHOP);
				break;
			case GEAR:
				sidemenu::open(sidemenu::GEAR_SHOP);
				break;
		}
	}
}
