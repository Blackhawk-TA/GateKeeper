//
// Created by daniel on 26.12.21.
//

#pragma once
#include "template/character.hpp"
#include "../../../game.hpp"

namespace combat {
	class Enemy : public Character {
	public:
		explicit Enemy(uint8_t save_id, CharacterData character_data);
		void start_round() override;
		void finish_round() override;
		CharacterType get_type() override;

	private:
		void handle_death() override;
	};
}
