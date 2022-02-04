//
// Created by daniel on 24.11.21.
//

#pragma once
#include "../../characters/template/character.hpp"

namespace game::character_handler {
	void init();
	void cleanup();
	void delete_character(Signature &signature);
	void animate(Timer &timer);
}
