//
// Created by daniel on 26.12.21.
//

#include "player.hpp"
#include "../ui/attack_menu.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Player::Player(uint8_t save_id, CharacterData character_data)
	: Character(save_id, character_data, Point(18, 11), Point(12, 11)) {
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

	Character::CharacterType Player::get_type() {
		return Character::Player;
	}

	void Player::start_round() {
		attack_menu::open();
	}

	void Player::handle_round_end() {
		attack_menu::close();
		character_handler::next_turn(this);
	}

	void Player::handle_death() {
		//TODO teleport to hospital
		character_handler::load_game_scene(save_id, false);
	}
}