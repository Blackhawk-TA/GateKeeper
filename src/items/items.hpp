//
// Created by daniel on 24.09.21.
//

#pragma once
#include "../engine/ui/listbox.hpp"
#include "../scenes/combat/characters/player.hpp"
#include "../scenes/combat/characters/enemy.hpp"

/**
 * Contains the create function for all inventory items
 */
namespace listbox_item {
	enum INVENTORY_ITEM {
		GATE_PART = 1,
		APPLE = 2,
		CARROT = 3,
		CARROT_SEED = 4,
		INVENTORY_BACK = 5
	};

	enum GEAR_ITEM {
		GEAR_BACK = 1,
	};

	enum SIDEMENU_ITEM {
		INVENTORY = 1,
		SAVE = 2,
		SIDEMENU_OPTIONS = 3,
		SIDEMENU_BACK = 4,
		QUIT = 5,
		GEAR = 6,
	};

	enum MENU_ITEM {
		LOAD_SAVE = 1,
		NEW_SAVE = 2,
		MENU_OPTIONS = 3
	};

	enum OPTIONS_ITEM {
		SHOW_FPS = 1,
		RESET_ALL = 2,
		OPTIONS_BACK = 3
	};

	enum COMBAT_ITEM {
		ESCAPE = 1,
		ATTACK_SWORD = 2,
		ATTACK_SPEAR = 3,
		ATTACK_ARROW = 4,
		ATTACK_DAGGER = 5,
		ATTACK_MAGIC = 6,
	};

	//Item generators
	Listbox::Item create_inventory_item(INVENTORY_ITEM item_type);
	Listbox::Item create_gear_item(GEAR_ITEM item_type);
	Listbox::Item create_sidemenu_item(SIDEMENU_ITEM item_type, uint8_t save_id = 0);
	Listbox::Item create_menu_item(MENU_ITEM item_type, uint8_t save_id = 0);
	Listbox::Item create_options_item(OPTIONS_ITEM item_type, uint8_t save_id = 0);
	Listbox::Item create_combat_item(COMBAT_ITEM item_type, uint8_t save_id = 0, combat::Player *player = nullptr, combat::Enemy *enemy = nullptr);

	//Generic items
	Listbox::Item create_options_entry(uint8_t type_id, uint8_t save_id = 0);

	//Inventory items
	Listbox::Item create_gate_part(uint8_t type_id);
	Listbox::Item create_apple(uint8_t type_id);
	Listbox::Item create_carrot(uint8_t type_id);
	Listbox::Item create_carrot_seed(uint8_t type_id);

	//Sidemenu items
	Listbox::Item create_inventory_entry(uint8_t type_id);
	Listbox::Item create_gear_entry(uint8_t type_id);
	Listbox::Item create_save_entry(uint8_t type_id, uint8_t save_id);
	Listbox::Item create_back_entry(uint8_t type_id);
	Listbox::Item create_quit_entry(uint8_t type_id);

	//Menu items
	Listbox::Item create_load_entry(uint8_t type_id, uint8_t save_id);
	Listbox::Item create_new_save_entry(uint8_t type_id, uint8_t save_id);

	//Options items
	Listbox::Item create_show_fps_entry(uint8_t type_id);
	Listbox::Item create_options_exit_entry(uint8_t type_id, uint8_t save_id = 0);
	Listbox::Item create_reset_all_entries(uint8_t type_id);

	//Combat items
	Listbox::Item create_combat_escape(uint8_t type_id, uint8_t save_id);
	Listbox::Item create_combat_attack_sword(uint8_t type_id, combat::Player *player, combat::Enemy *enemy);
	Listbox::Item create_combat_attack_spear(uint8_t type_id, combat::Player *player, combat::Enemy *enemy);
	Listbox::Item create_combat_attack_arrow(uint8_t type_id, combat::Player *player, combat::Enemy *enemy);
	Listbox::Item create_combat_attack_dagger(uint8_t type_id, combat::Player *player, combat::Enemy *enemy);
	Listbox::Item create_combat_attack_magic(uint8_t type_id, combat::Player *player, combat::Enemy *enemy);
}
