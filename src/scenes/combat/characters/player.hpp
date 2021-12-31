//
// Created by daniel on 26.12.21.
//

#pragma once
#include "template/character.hpp"

namespace combat {
	class Player : public Character {
	public:
		explicit Player(CharacterData character_data);
		uint8_t get_stamina() const;
		static const uint8_t MAX_STAMINA = 100;

	private:
		uint8_t stamina;
	};
}
