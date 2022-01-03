//
// Created by daniel on 26.12.21.
//

#pragma once
#include "template/character.hpp"

namespace combat {
	class Player : public Character {
	public:
		static const uint8_t MAX_STAMINA = 100;

		explicit Player(CharacterData character_data);
		uint8_t get_stamina() const;
		bool use_stamina(uint8_t amount) override;
		void attack() override;
		void finish_attack() override;
		CharacterType get_type() override;

	private:
		uint8_t stamina;
	};
}
