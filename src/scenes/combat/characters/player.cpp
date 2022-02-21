//
// Created by daniel on 26.12.21.
//

#include "player.hpp"
#include "../ui/attack_menu.hpp"
#include "../handlers/character_handler.hpp"

namespace combat {
	Player::Player(uint8_t save_id, const CharacterData& character_data)
	: Character(save_id, character_data, Point(18, 11), Point(12, 11), LEFT) {
		stamina = MAX_STAMINA;
		stats = character_data.stats;
	}

	uint8_t Player::get_stamina() const {
		return stamina;
	}

	bool Player::use_stamina(uint8_t amount) {
		if (stamina - amount >= 0) {
			stamina -= amount;
			return true;
		} else {
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
		SceneOptions options = {
			save_id,
			{},
			{},
			true,
		};
		load_scene(GAMEOVER, options);
	}
}