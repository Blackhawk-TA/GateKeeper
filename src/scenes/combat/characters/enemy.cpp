//
// Created by daniel on 26.12.21.
//

#include "enemy.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Enemy::Enemy(uint8_t save_id, Character *target, CharacterData character_data)
	: Character(save_id, character_data, Point(11, 11), Point(17, 11), RIGHT) {
		Enemy::target = target;
		Enemy::signature = character_data.signature;
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
		if (is_animal()) {
			textbox = new Textbox("Enemy is attacking!");
			character_handler::attack(MELEE, this, target);
		} else {
			uint8_t rand = blit::random() % 10;

			//TODO dont always allow all attacks.
			if (rand < 4) { //40% chance for sword attack
				textbox = new Textbox("Enemy is executing a sword attack!");
				character_handler::attack(MELEE, this, target);
			} else if (rand < 6) { // 20% chance for spear attack
				textbox = new Textbox("Enemy is throwing a spear!");
				character_handler::attack(SPEAR, this, target);
			} else if (rand < 8) { // 20% chance for arrow attack
				textbox = new Textbox("Enemy is shooting an arrow!");
				character_handler::attack(ARROW, this, target);
			} else if (rand < 9) { // 10% chance for dagger attack
				textbox = new Textbox("Enemy is throwing a dagger!");
				character_handler::attack(DAGGER, this, target);
			} else { //10% change for magic attack
				textbox = new Textbox("Enemy is using magic!");
				character_handler::attack(MAGIC, this, target);
			}
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

	Signature Enemy::get_signature() {
		return signature;
	}

	bool Enemy::is_animal() {
		uint16_t default_tile_id = movement_sprites.at(0);
		return default_tile_id == 104 || default_tile_id == 224 || default_tile_id == 228 || default_tile_id == 232 || default_tile_id == 236;
	}
}
