//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../engine/ui/listbox.hpp"
#include "../characters/enemy.hpp"
#include "../characters/player.hpp"

namespace combat::attack_menu {
	void init(uint8_t save_id, Player *player, Enemy *enemy);
	void cleanup();
	void open();
	void close();
	bool is_open();
	bool add_item(Listbox::Item item);
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
