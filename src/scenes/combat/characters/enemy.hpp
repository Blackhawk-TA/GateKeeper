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
		explicit Enemy(uint8_t save_id, Character *target, const CharacterData& character_data);
		~Enemy() override;
		void draw() override;
		void start_round() override;
		void handle_round_end() override;
		CharacterType get_type() override;
		Signature get_signature();

	private:
		Signature signature;
		Character *target;
		Textbox *textbox;
		CombatCharacterType enemy_type;
		void handle_death() override;
	};
}
