//
// Created by daniel on 26.12.21.
//

#pragma once
#include "template/character.hpp"

namespace combat {
	class Player : public Character {
	public:
		explicit Player(CharacterData character_data);
	};
}
