//
// Created by daniel on 24.09.21.
//

#include "items.hpp"
#include "../game.hpp"

Listbox::Item listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM item_type) {
	Listbox::Item item;

	switch (item_type) {
		case INVENTORY_ITEM::GATE_PART:
			item = create_gate_part();
			break;
		case INVENTORY_ITEM::EXIT_INVENTORY:
			item = create_exit_entry();
			break;
	}

	return item;
}

Listbox::Item listbox_item::create_sidemenu_item(listbox_item::MENU_ITEM item_type, uint8_t save_id) {
	Listbox::Item item;

	switch (item_type) {
		case MENU_ITEM::INVENTORY:
			item = create_inventory_entry();
			break;
		case MENU_ITEM::SHOW_FPS:
			item = create_show_fps_entry();
			break;
		case MENU_ITEM::SAVE:
			item = create_save_entry(save_id);
			break;
		case MENU_ITEM::EXIT:
			item = create_exit_entry();
			break;
	}

	return item;
}

Listbox::Item listbox_item::create_menu_item(uint8_t save_id) {
	std::string save_id_str = std::to_string(save_id);

	return Listbox::Item{
		"Save " + save_id_str,
		"Load saved game " + save_id_str,
		"Loading save...",
		"",
		false,
		0,
		[save_id] {
			load_game_scene(save_id);
			return Listbox::Tooltip::SUCCESS;
		}
	};
}

