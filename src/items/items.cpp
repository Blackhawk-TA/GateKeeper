//
// Created by daniel on 24.09.21.
//

#include "items.hpp"

namespace listbox_item {
	Listbox::Item create_inventory_item(INVENTORY_ITEM item_type) {
		Listbox::Item item;

		switch (item_type) {
			case INVENTORY_ITEM::GATE_PART:
				item = create_gate_part(INVENTORY_ITEM::GATE_PART);
				break;
			case INVENTORY_ITEM::APPLE:
				item = create_apple(INVENTORY_ITEM::APPLE);
				break;
			case INVENTORY_ITEM::CARROT:
				item = create_carrot(INVENTORY_ITEM::CARROT);
				break;
			case INVENTORY_ITEM::CARROT_SEED:
				item = create_carrot_seed(INVENTORY_ITEM::CARROT_SEED);
				break;
			case INVENTORY_ITEM::INVENTORY_BACK:
				item = create_back_entry(INVENTORY_ITEM::INVENTORY_BACK);
				break;
		}

		return item;
	}

	Listbox::Item create_sidemenu_item(SIDEMENU_ITEM item_type, uint8_t save_id) {
		Listbox::Item item;

		switch (item_type) {
			case SIDEMENU_ITEM::INVENTORY:
				item = create_inventory_entry(SIDEMENU_ITEM::INVENTORY);
				break;
			case SIDEMENU_ITEM::SAVE:
				item = create_save_entry(SIDEMENU_ITEM::SAVE, save_id);
				break;
			case SIDEMENU_ITEM::SIDEMENU_OPTIONS:
				item = create_options_entry(SIDEMENU_ITEM::SIDEMENU_BACK, save_id);
				break;
			case SIDEMENU_ITEM::SIDEMENU_BACK:
				item = create_back_entry(SIDEMENU_ITEM::SIDEMENU_BACK);
				break;
			case SIDEMENU_ITEM::QUIT:
				item = create_quit_entry(SIDEMENU_ITEM::QUIT);
				break;
		}

		return item;
	}

	Listbox::Item create_menu_item(MENU_ITEM item_type, uint8_t save_id) {
		std::string save_id_str = std::to_string(save_id);

		Listbox::Item item;

		switch (item_type) {
			case MENU_ITEM::LOAD_SAVE:
				item = create_load_entry(MENU_ITEM::LOAD_SAVE, save_id);
				break;
			case MENU_ITEM::NEW_SAVE:
				item = create_new_save_entry(MENU_ITEM::NEW_SAVE, save_id);
				break;
			case MENU_ITEM::MENU_OPTIONS:
				item = create_options_entry(MENU_ITEM::MENU_OPTIONS);
				break;
		}

		return item;
	}

	Listbox::Item create_options_item(OPTIONS_ITEM item_type, uint8_t save_id) {
		Listbox::Item item;

		switch (item_type) {
			case OPTIONS_ITEM::SHOW_FPS:
				item = create_show_fps_entry(OPTIONS_ITEM::SHOW_FPS);
				break;
			case OPTIONS_ITEM::OPTIONS_BACK:
				item = create_options_exit_entry(OPTIONS_ITEM::OPTIONS_BACK, save_id);
				break;
		}

		return item;
	}

	Listbox::Item create_combat_item(COMBAT_ITEM item_type, uint8_t save_id, combat::Player *player, combat::Enemy *enemy) {
		Listbox::Item item;

		switch (item_type) {
			case COMBAT_ITEM::ESCAPE:
				item = create_combat_escape(COMBAT_ITEM::ESCAPE, save_id);
				break;
			case COMBAT_ITEM::ATTACK_LIGHT:
				item = create_combat_attack_light(COMBAT_ITEM::ATTACK_LIGHT, player, enemy);
				break;
			case COMBAT_ITEM::ATTACK_HEAVY:
				item = create_combat_attack_heavy(COMBAT_ITEM::ATTACK_HEAVY, player, enemy);
				break;
			case ATTACK_RANGE:
				break;
			case ATTACK_MAGIC:
				break;
		}

		return item;
	}
}