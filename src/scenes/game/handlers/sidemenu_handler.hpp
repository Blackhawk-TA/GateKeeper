//
// Created by daniel on 24.01.22.
//

#pragma once
#include "../../../utils/utils.hpp"
#include "../../../engine/ui/listbox.hpp"
#include "../../../utils/saves/save_types.hpp"

namespace game::sidemenu {
	enum MenuType {
		NO_MENU = 0,
		MAIN = 1,
		INVENTORY = 2,
		GEAR = 3,
	};

	struct MenuData {
		bool is_inventory;
		Rect rect;
		std::vector<Listbox::Item> items;
	};

	void init(uint8_t save_id);
	void cleanup();
	std::array<std::array<save::Item, MAX_ITEMS>, save::MAX_INVENTORIES> get_saves();
	void load_saves(std::array<std::array<save::Item, MAX_ITEMS>, save::MAX_INVENTORIES> &save_items);
	void open(MenuType menu_type);
	void close();
	void navigate_back();
	bool add_item(MenuType menu_type, Listbox::Item item);
	bool is_open();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
