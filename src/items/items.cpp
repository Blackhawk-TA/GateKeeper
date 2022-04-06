//
// Created by daniel on 24.09.21.
//

#include "items.hpp"

namespace items {
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
			case SIDEMENU_ITEM::GEAR:
				item = create_gear_entry(SIDEMENU_ITEM::GEAR);
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
			case OPTIONS_ITEM::SHOW_TIME:
				item = create_show_time_entry(OPTIONS_ITEM::SHOW_TIME);
				break;
			case OPTIONS_ITEM::OPTIONS_BACK:
				item = create_options_exit_entry(OPTIONS_ITEM::OPTIONS_BACK, save_id);
				break;
			case RESET_ALL:
				item = create_reset_all_entries(OPTIONS_ITEM::RESET_ALL);
				break;
		}

		return item;
	}

	Listbox::Item create_combat_item(COMBAT_ITEM item_type, uint8_t save_id, combat::Player *player, combat::Enemy *enemy) {
		Listbox::Item item;

		switch (item_type) {
			case COMBAT_ITEM::ESCAPE:
				item = create_combat_escape(item_type, save_id);
				break;
			case ATTACK_SWORD:
				item = create_combat_attack_sword(item_type, player, enemy);
				break;
			case ATTACK_SPEAR:
				item = create_combat_attack_spear(item_type, player, enemy);
				break;
			case ATTACK_ARROW:
				item = create_combat_attack_arrow(item_type, player, enemy);
				break;
			case ATTACK_DAGGER:
				item = create_combat_attack_dagger(item_type, player, enemy);
				break;
			case ATTACK_MAGIC:
				item = create_combat_attack_magic(item_type, player, enemy);
				break;
			case ATTACK_FIRE:
				item = create_combat_attack_fire(item_type, player, enemy);
				break;
			case ATTACK_ICE:
				item = create_combat_attack_ice(item_type, player, enemy);
				break;
			case ATTACK_SHOCK:
				item = create_combat_attack_shock(item_type, player, enemy);
				break;
		}

		return item;
	}

	Listbox::Item create_gear_item(GEAR_TYPE item_type) {
		Listbox::Item item;

		switch (item_type) {
			case GEAR_SWORD:
				item = create_gear_sword(item_type);
				break;
			case GEAR_SPEAR:
				item = create_gear_spear(item_type);
				break;
			case GEAR_ARROW:
				item = create_gear_arrow(item_type);
				break;
			case GEAR_DAGGER:
				item = create_gear_dagger(item_type);
				break;
			case GEAR_MAGIC:
				item = create_gear_magic(item_type);
				break;
			case GEAR_FIRE:
				item = create_gear_fire(item_type);
				break;
			case GEAR_ICE:
				item = create_gear_ice(item_type);
				break;
			case GEAR_SHOCK:
				item = create_gear_shock(item_type);
				break;
			case GEAR_NAVIGATE_BACK:
				item = create_back_entry(item_type);
				break;
			default:
				break;
		}

		return item;
	}

	Listbox::Item create_shop_item(SHOP_ITEM item_type) {
		Listbox::Item item;

		switch (item_type) {
			case SHOP_APPLE:
				item = create_shop_apple(item_type);
				break;
			case SHOP_CARROT:
				item = create_shop_carrot(item_type);
				break;
			case SHOP_CARROT_SEED:
				item = create_shop_carrot_seed(item_type);
				break;
			case SHOP_SWORD:
				item = create_shop_sword(item_type);
				break;
			case SHOP_DAGGER:
				item = create_shop_dagger(item_type);
				break;
			case SHOP_ARROW:
				item = create_shop_arrow(item_type);
				break;
			case SHOP_SPEAR:
				item = create_shop_spear(item_type);
				break;
			case SHOP_BACK:
				item = create_back_entry(item_type);
				break;
		}

		return item;
	}
}