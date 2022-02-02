//
// Created by daniel on 24.01.22.
//

#include "sidemenu_handler.hpp"
#include "../ui/inventory.hpp"

namespace game::sidemenu {
	std::map<MenuType, MenuData> menu_data;
	std::map<MenuType, Listbox*> controls;
	std::vector<ui::Inventory*> inventories;
	MenuType previous_sidemenu;
	MenuType current_sidemenu;

	void init(uint8_t save_id) {
		current_sidemenu = NO_MENU;
		previous_sidemenu = NO_MENU;
		menu_data = {
			{
				MAIN,
				MenuData{
					false,
					Rect(16, 0, 4, 8),
					{
						listbox_item::create_sidemenu_item(listbox_item::INVENTORY),
						listbox_item::create_sidemenu_item(listbox_item::GEAR),
						listbox_item::create_sidemenu_item(listbox_item::SIDEMENU_OPTIONS, save_id),
						listbox_item::create_sidemenu_item(listbox_item::SAVE, save_id),
						listbox_item::create_sidemenu_item(listbox_item::SIDEMENU_BACK),
						listbox_item::create_sidemenu_item(listbox_item::QUIT)
					}
				}
			}, {
				INVENTORY,
				MenuData{
					true,
					Rect(14, 0, 6, 7),
					{
						//TODO remove free items
						listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::CARROT_SEED),
						listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::INVENTORY_BACK)
					}
				}
			}, {
				GEAR,
				MenuData{
					true,
					Rect(14, 0, 6, 7),
					{
						listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::INVENTORY_BACK)
					}
				}
			}
		};

		controls = {};
		inventories = {};
		ui::Inventory *inventory;
		for (auto &itr : menu_data) {
			if (itr.second.is_inventory) {
				inventory = new ui::Inventory(itr.second.rect, itr.second.items);
				inventories.emplace_back(inventory);
				controls.insert(std::make_pair(itr.first, inventory));
			} else {
				controls.insert(std::make_pair(itr.first, new Listbox(itr.second.rect, itr.second.items)));
			}
		}
	}

	void cleanup() {
		for (auto &control : controls) {
			delete control.second;
		}

		controls.clear();
		inventories.clear();
	}

	std::array<std::array<save::Item, MAX_ITEMS>, save::MAX_INVENTORIES> get_saves() {
		std::array<std::array<save::Item, MAX_ITEMS>, save::MAX_INVENTORIES> saves = {};

		for (uint8_t i = 0u; i < inventories.size(); i++) {
			saves.at(i) = inventories.at(i)->get_save();
		}

		return saves;
	}

	void load_saves(std::array<std::array<save::Item, MAX_ITEMS>, save::MAX_INVENTORIES> &save_items) {
		for (uint8_t i = 0u; i < inventories.size(); i++) {
			inventories.at(i)->load_save(save_items.at(i));
		}
	}

	void open(MenuType menu_type) {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->cursor_reset();
		}
		if (controls.find(menu_type) != controls.end()) {
			previous_sidemenu = current_sidemenu;
			current_sidemenu = menu_type;
		}
	}

	void close() {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->cursor_reset();
		}
		previous_sidemenu = current_sidemenu;
		current_sidemenu = NO_MENU;
	}

	void navigate_back() {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->cursor_reset();
			current_sidemenu = previous_sidemenu;
			previous_sidemenu = NO_MENU; //Allows only one sub menu regarding menu depth
		}
	}

	bool add_item(MenuType menu_type, Listbox::Item item) {
		if (menu_data.at(menu_type).is_inventory) {
			return controls.at(menu_type)->add_item(item);
		}
		return false;
	}

	bool is_open() {
		return current_sidemenu != NO_MENU;
	}

	void draw() {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->draw();
		}
	}

	void cursor_up() {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->cursor_up();
		}
	}

	void cursor_down() {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->cursor_down();
		}
	}

	void cursor_press() {
		if (controls.find(current_sidemenu) != controls.end()) {
			controls.at(current_sidemenu)->cursor_press();
		}
	}
}
