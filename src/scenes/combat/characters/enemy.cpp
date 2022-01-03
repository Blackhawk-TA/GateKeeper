//
// Created by daniel on 26.12.21.
//

#include "enemy.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Enemy::Enemy(CharacterData character_data)
	: Character(character_data, Point(11, 11), Point(17, 11)) {
		direction = RIGHT;
		health = MAX_HEALTH;
	}

	Character::CharacterType Enemy::get_type() {
		return Character::Enemy;
	}

	void Enemy::attack() {
		//TODO implement enemy attack
	}

	void Enemy::finish_attack() {
		character_handler::next_turn(this);
	}
}
