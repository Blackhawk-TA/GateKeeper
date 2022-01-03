//
// Created by daniel on 26.12.21.
//

#pragma once
#include "template/character.hpp"
#include "../../../game.hpp"
#include "player.hpp"
#include "../../../engine/ui/textbox.hpp"

namespace combat {
	class Enemy : public Character {
	public:
		explicit Enemy(uint8_t save_id, Character *target, CharacterData character_data);
		void draw() override;
		void start_round() override;
		void finish_round() override;
		CharacterType get_type() override;

	private:
		Character *target;
		Textbox *textbox;
		void handle_death() override;
	};
}
