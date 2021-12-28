//
// Created by daniel on 24.11.21.
//

#pragma once
#include "../../../game_objects/characters/template/character.hpp"

namespace game::character_handler {
	void init();
	void cleanup();
	void animate(Timer &timer);
}
