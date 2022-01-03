//
// Created by daniel on 26.12.21.
//

#include "enemy.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Enemy::Enemy(uint8_t save_id, Character *target, CharacterData character_data)
	: Character(save_id, character_data, Point(11, 11), Point(17, 11)) {
		Enemy::target = target;
		direction = RIGHT;
		health = MAX_HEALTH;
		textbox = nullptr;
	}

	Enemy::~Enemy() {
		if (textbox != nullptr) {
			delete textbox;
			textbox = nullptr;
		}

		//Is already deleted by character_handler
		target = nullptr;
	}

	Character::CharacterType Enemy::get_type() {
		return Character::Enemy;
	}

	void Enemy::start_round() {
		uint8_t rand = blit::random() % 10;

		if (rand < 4) { //40% chance for light attack
			textbox = new Textbox("Enemy is executing a light sword attack!");
			character_handler::attack_light(this, target);
		} else if (rand < 6) { // 20% chance for heavy attack
			textbox = new Textbox("Enemy is executing an heavy sword attack!");
			character_handler::attack_light(this, target);
		} else if (rand < 9) { // 30% chance for range attack
			textbox = new Textbox("Enemy is executing a range attack!");
			character_handler::attack_light(this, target);
		} else { // 10% chance for magic attack
			textbox = new Textbox("Enemy is executing a magic attack!");
			character_handler::attack_light(this, target);
		}
	}

	void Enemy::handle_round_end() {
		delete textbox;
		textbox = nullptr;
		character_handler::next_turn(this);
	}

	void Enemy::handle_death() {
		//TODO remove enemy from game objects and set player health
		character_handler::load_game_scene(save_id, true);
	}

	void Enemy::draw() {
		Character::draw();

		if (textbox != nullptr) {
			textbox->draw();
		}
	}
}
