//
// Created by daniel on 24.11.21.
//

#include "villager.hpp"
#include <utility>

namespace game {
	Villager::Villager(map::MapSection map_section, Point position, uint16_t tile_id, MovementDirection direction, std::string message)
		: Character(map_section, position, true, false, true) {
		Villager::message = std::move(message);
		Villager::tile_id = tile_id;
		set_movement_sprites();
		change_direction(direction, false);
	}

	bool Villager::player_interact() {
		bool interacted = Character::player_interact();

		if (interacted) {
			textbox = new Textbox(message);
			return true;
		}

		return false;
	}

	//Prevent player from looking away directly after closing textbox
	void Villager::close_textbox() {
		GameObject::close_textbox();
		last_turn = blit::now();
	}

	void Villager::set_state(uint8_t new_state) {}

	void Villager::update_state(Point next_position) {}
}
