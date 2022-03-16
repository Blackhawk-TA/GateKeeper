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
		ITEM_SHOP = 4,
		GEAR_SHOP = 5,
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
	std::vector<Listbox::Item> get_items(MenuType menu_type);

	/**
	 * Checks if an item exists in the menu list no matter of the amount. This function is memory intensive and should be used only when necessary.
	 * @param menu_type The menu type enum operator stating in which enum to check for
	 * @param item The item whose existence is checked
	 * @return True if the item exists, else false
	 */
	bool has_item(MenuType menu_type, Listbox::Item &item);
	bool add_item(MenuType menu_type, Listbox::Item item, uint8_t amount = 1);
	void clear_items(MenuType menu_type);
	bool is_open();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
}
