//
// Created by daniel on 28.02.22.
//

#pragma once
#include "../../../../utils/movement_direction.hpp"
#include "../../../../utils/types.hpp"
#include "../../../../utils/saves/save_types.hpp"

namespace game::player_handler {
	void init(uint8_t save_id);
	void cleanup();
	void draw();
	void animate(Timer &timer);
	void move(MovementDirection direction);
	uint8_t get_health();
	void heal(uint8_t heal_amount);
	MovementDirection get_direction();
	void change_direction(MovementDirection direction, bool animate = true);
	void set_cut_scene(bool value);
	bool in_cut_scene();
	uint16_t get_gold();
	void add_gold(uint16_t amount);
	bool remove_gold(uint16_t amount);
	CharacterData get_character_data();
	save::PlayerData get_save();
	void load_save(save::PlayerData save_data);
}
