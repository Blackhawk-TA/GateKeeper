//
// Created by daniel on 15.03.22.
//

#include "chest.hpp"
#include "../handler/player_handler.hpp"

namespace game {
	Chest::Chest(map::MapSection map_section, Point position) : GameObject(map_section, position, true, false){
		Chest::set_state(CLOSED);
		size = Size(1, 1);
	}

	bool Chest::player_interact() {
		if (state == CLOSED && player_usable && player_in_front()) {
			uint16_t gold = blit::random() % 15 + 15;
			textbox = new Textbox("You found " + std::to_string(gold) + " gold in the chest.");
			player_handler::add_gold(gold);
			set_state(OPEN);
			return true;
		} else if (state == OPEN && player_in_front()){
			textbox = new Textbox("The chest is empty.");
			return false;
		}
	}

	GameObject::ObjectType Chest::get_type() {
		return GameObject::ChestType;
	}

	void Chest::load_save(Data data) {
		GameObject::load_save(data);

		//Update chest state once the save was loaded
		if (player_usable) {
			set_state(CLOSED);
		} else {
			set_state(OPEN);
		}
	}

	void Chest::set_state(uint8_t new_state) {
		auto new_state_enum = static_cast<State>(new_state);

		switch (new_state_enum) {
			case OPEN:
				tile_id = OPENED_TILE_ID;
				set_player_usable(false);
				break;
			case CLOSED:
				tile_id = CLOSED_TILE_ID;
				break;
		}

		state = new_state_enum;
	}
}
