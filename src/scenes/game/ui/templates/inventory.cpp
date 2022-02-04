//
// Created by daniel on 24.01.22.
//

#include <cassert>
#include "inventory.hpp"

namespace game::ui_template {
	Inventory::Inventory(Rect rect, std::vector<Item> &items) : Listbox(rect, items, true) {
		Inventory::rect = rect;
		Inventory::items = items;
	}

	std::array<save::Item, MAX_ITEMS> Inventory::get_save() {
		std::array<save::Item, MAX_ITEMS> compressed_items = {};
		uint8_t amount;

		assert(items.size() <= MAX_ITEMS);

		for (auto i = 0u; i < items.size(); i++) {
			amount = i < items.size() ? items[i].amount : 0;
			compressed_items[i] = save::Item{
				items[i].type,
				amount
			};
		}

		return compressed_items;
	}

	void Inventory::load_save(std::array<save::Item, MAX_ITEMS> &save_items) {
		std::vector<Listbox::Item> decompressed_items = {};
		Listbox::Item item_template;

		uint8_t i = 0;
		save::Item *item;
		bool array_end = false;

		while (!array_end && i < MAX_ITEMS) {
			item = &save_items[i];

			if (item->type == 0 && item->amount == 0) {
				array_end = true;
				continue;
			}

			item_template = listbox_item::create_inventory_item(static_cast<listbox_item::INVENTORY_ITEM>(item->type));

			//Include only items that have an amount > 0 or are a menu item
			if (item->type > 0 && (item->amount > 0 || (item->amount == 0 && !item_template.single_use))) {
				decompressed_items.emplace_back(Listbox::Item{
					item->type,
					item_template.name,
					item_template.tooltip,
					item_template.callback_tooltip,
					item_template.callback_fail_tooltip,
					item_template.single_use,
					item->amount,
					item_template.callback
				});
			}
			i++;
		}

		items = decompressed_items;
	}
}
