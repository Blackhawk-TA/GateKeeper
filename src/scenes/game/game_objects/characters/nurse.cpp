//
// Created by daniel on 17.01.22.
//

#include "nurse.hpp"
#include "../player.hpp"

namespace game {
	Nurse::Nurse(map::MapSection map_section, Point position) : Character(map_section, position, true, false) {
		tile_id = TILE_ID;
		set_movement_sprites();
	}

	bool Nurse::player_interact() {
		if (player_usable && player_in_front(BAR_HEIGHT)) {
			if (Player::get_health() == Player::MAX_HEALTH) {
				textbox = new Textbox("Hello, I'm the nurse here. I can heal you if you want, but you seem be healthy.");
			} else {
				textbox = new Textbox("Hello, I'm the nurse here. You look injured, let me heal you!");
				Player::heal(Player::MAX_HEALTH);
			}

			return true;
		}

		return false;
	}

	void Nurse::set_state(uint8_t new_state) {}

	void Nurse::update(uint32_t time) {}

	void Nurse::update_state(Point next_position) {}
}