//
// Created by daniel on 26.12.21.
//

#include "player.hpp"

namespace combat {
	Player::Player(CharacterData character_data)
	: Character(character_data, Point(18, 11), Point(12, 11)) {
		direction = LEFT;
		stamina = MAX_STAMINA;
	}

	uint8_t Player::get_stamina() const {
		return stamina;
	}

	bool Player::use_stamina(uint8_t amount) {
		if (stamina - amount > 0) {
			stamina -= amount;
			return true;
		} else {
			stamina = 0;
			return false;
		}
	}
}