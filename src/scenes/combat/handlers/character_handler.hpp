//
// Created by daniel on 30.12.21.
//

#pragma once
#include "../characters/template/character.hpp"
#include "../characters/enemy.hpp"
#include "../characters/player.hpp"

namespace combat::character_handler {
	void init(uint8_t save_id, const CombatData& combat_data);
	void cleanup();
	void draw();
	void update(uint32_t time);
	void animate(Timer &timer);
	Enemy *get_enemy();
	Player *get_player();
	void next_turn(Character *last_turn);
	void load_game_scene(uint8_t save_id, bool respawn, bool won_fight);
	bool escape();
	bool attack(GEAR_TYPE type, Character *attacker, Character *target);
}
