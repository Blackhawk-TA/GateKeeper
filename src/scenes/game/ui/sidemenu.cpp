//
// Created by daniel on 24.01.22.
//

#include "sidemenu.hpp"
#include "templates/inventory.hpp"

namespace game::sidemenu {
	std::map<MenuType, MenuData> menu_data;
	std::map<MenuType, Listbox*> controls;
	std::vector<Inventory*> inventories = {};
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
						items::create_sidemenu_item(items::INVENTORY),
						items::create_sidemenu_item(items::GEAR),
						items::create_sidemenu_item(items::SIDEMENU_OPTIONS, save_id),
						items::create_sidemenu_item(items::SAVE, save_id),
						items::create_sidemenu_item(items::SIDEMENU_BACK),
						items::create_sidemenu_item(items::QUIT)
					}
				}
			}, {
				INVENTORY,
				MenuData{
					true,
					Rect(14, 0, 6, 7),
					{
						items::create_inventory_item(items::INVENTORY_ITEM::INVENTORY_BACK)
					}
				}
			}, {
				GEAR,
				MenuData{
					true,
					Rect(14, 0, 6, 11),
					{
						items::create_gear_item(GEAR_SWORD),
						items::create_gear_item(GEAR_SPEAR),
						items::create_gear_item(GEAR_ARROW),
						items::create_gear_item(GEAR_NAVIGATE_BACK),
					}
				}
			}, {
				ITEM_SHOP,
				MenuData{
					false,
					Rect(15, 0, 5, 8),
					{
						items::create_shop_item(items::SHOP_APPLE),
						items::create_shop_item(items::SHOP_CARROT),
						items::create_shop_item(items::SHOP_CARROT_SEED),
						items::create_shop_item(items::SHOP_BACK),
					},
				}
			}, {
				GEAR_SHOP,
				MenuData{
					false,
					Rect(16, 0, 4, 8),
					{
						items::create_shop_item(items::SHOP_ARROW),
						items::create_shop_item(items::SHOP_DAGGER),
						items::create_shop_item(items::SHOP_SPEAR),
						items::create_shop_item(items::SHOP_SWORD),
						items::create_shop_item(items::SHOP_BACK),
					},
				}
			}
		};

		controls = {};
		inventories = {};
		Inventory *inventory;
		for (auto &itr : menu_data) {
			if (itr.second.is_inventory) {
				inventory = new Inventory(itr.first, itr.second.rect, itr.second.items);
				inventories.emplace_back(inventory);
				controls.insert(std::make_pair(itr.first, inventory));
			} else {
				controls.insert(std::make_pair(itr.first, new Listbox(itr.second.rect, itr.second.items, false)));
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

	std::vector<Listbox::Item> get_items(MenuType menu_type) {
		if (menu_data.find(menu_type) != menu_data.end()) {
			return controls.at(menu_type)->get_items();
		}
		return {};
	}

	bool has_item(MenuType menu_type, Listbox::Item &item) {
		std::vector<Listbox::Item> items = get_items(menu_type);

		return std::any_of(items.begin(), items.end(), [item](Listbox::Item &tmp_item) {
			return tmp_item.type == item.type;
		});
	}

	bool add_item(MenuType menu_type, Listbox::Item item, uint8_t amount) {
		if (menu_data.at(menu_type).is_inventory) {
			return controls.at(menu_type)->add_item(item, amount);
		}
		return false;
	}

	void clear_items(MenuType menu_type) {
		if (!menu_data.at(menu_type).is_inventory) {
			return;
		}
		std::vector<Listbox::Item> old_items = get_items(menu_type);
		std::vector<Listbox::Item> new_items = {};

		for (auto &item : old_items) {
			if (item.sort_to_bottom) { //Move menu items to new items list
				new_items.emplace_back(item);
			}
		}

		controls.at(menu_type)->set_items(new_items);
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
