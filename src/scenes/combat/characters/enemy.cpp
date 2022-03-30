//
// Created by daniel on 26.12.21.
//

#include "enemy.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Enemy::Enemy(uint8_t save_id, Character *target, const CharacterData& character_data)
	: Character(save_id, character_data, Point(11, 11), Point(17, 11), RIGHT) {
		Enemy::target = target;
		Enemy::signature = character_data.signature;
		stats = character_data.stats;
		health = MAX_HEALTH;
		enemy_type = character_data.character_type;
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
		GEAR_TYPE attack = stats.attacks[blit::random() % stats.attacks.size()];

		textbox = new Textbox("Enemy is attacking!");
		character_handler::attack(attack, this, target);
	}

	void Enemy::handle_round_end() {
		delete textbox;
		textbox = nullptr;
		character_handler::next_turn(this);
	}

	void Enemy::handle_death() {
		//The red guard is the end boss. If he is defeated, the game is over.
		bool finished_game = enemy_type == CombatCharacterType::RED_GUARD;

		character_handler::load_game_scene(save_id, true, finished_game);
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
}
