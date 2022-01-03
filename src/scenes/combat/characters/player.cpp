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
		//TODO hide selection listbox on attack but keep textbox visible, textbox also shows information about enemy attack
		// selection box has to be immediately hidden on press attack, otherwise it could be pressed twice
		// also make sure it can only be pressed once, regarding fast clicks
		// alternatively hide attack_menu and only shows newly created textbox for enemy attack information
	}

	void Player::finish_round() {
		attack_menu::close();
		character_handler::next_turn(this);
	}

	void Player::handle_death() {
		//TODO teleport to hospital
		SceneOptions options = {
			save_id,
			{},
			true,
			true
		};
		load_scene(SceneType::GAME, options);
	}
}