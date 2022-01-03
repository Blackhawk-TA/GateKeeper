//
// Created by daniel on 26.12.21.
//

#include "enemy.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Enemy::Enemy(uint8_t save_id, CharacterData character_data)
	: Character(save_id, character_data, Point(11, 11), Point(17, 11)) {
		direction = RIGHT;
		health = MAX_HEALTH;
	}

	Character::CharacterType Enemy::get_type() {
		return Character::Enemy;
	}

	void Enemy::start_round() {
		//TODO implement enemy attack
	}

	void Enemy::finish_round() {
		character_handler::next_turn(this);
	}

	void Enemy::handle_death() {
		//TODO remove enemy from game objects
		SceneOptions options = {
			save_id,
			{},
			true,
			true
		};
		load_scene(SceneType::GAME, options);
	}
}
