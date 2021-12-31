//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../engine/ui/listbox.hpp"
#include "../characters/enemy.hpp"
#include "../characters/player.hpp"

namespace combat::attack_menu {
	inline Listbox *control;
	inline std::vector<Listbox::Item> items;

	void init(uint8_t save_id, Player *player, Enemy *enemy);
	void open();
	void close();
	bool is_open();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
