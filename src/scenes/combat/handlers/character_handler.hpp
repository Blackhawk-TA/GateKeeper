//
// Created by daniel on 30.12.21.
//

#pragma once
#include "../characters/template/character.hpp"
#include "../characters/enemy.hpp"
#include "../characters/player.hpp"

namespace combat::character_handler {
	void init(CombatData combat_data);
	void cleanup();
	void draw();
	void update(uint32_t time);
	void animate(Timer &timer);
	Enemy *get_enemy();
	Player *get_player();
}