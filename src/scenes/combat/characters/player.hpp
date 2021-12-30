//
// Created by daniel on 26.12.21.
//

#pragma once
#include "template/character.hpp"

namespace combat {
	class CombatPlayer : public Character {
	public:
		explicit CombatPlayer(CharacterData character_data);
	};
}
