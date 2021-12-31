//
// Created by daniel on 26.12.21.
//

#include "enemy.hpp"

namespace combat {
	Enemy::Enemy(CharacterData character_data)
	: Character(character_data, Point(11, 11), Point(17, 11)) {
		direction = RIGHT;
		health = MAX_HEALTH;
	}
}
