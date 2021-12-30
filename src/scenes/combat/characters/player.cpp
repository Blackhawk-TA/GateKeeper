//
// Created by daniel on 26.12.21.
//

#include "player.hpp"

namespace combat {
	Player::Player(CharacterData character_data)
	: Character(character_data, Point(18, 11), Point(12, 11)) {
		direction = LEFT;
	}
}