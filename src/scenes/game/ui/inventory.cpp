//
// Created by daniel on 23.09.21.
//

#include <cassert>
#include "inventory.hpp"

namespace game::inventory {
	Listbox *control;
	bool open_state = false;

	void init() {
		std::vector<Listbox::Item> items = {
			//TODO remove free items
			listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::CARROT_SEED),
			listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::INVENTORY_BACK)
		};
		control = new Listbox(Rect(14, 0, 6, 7), items);
	}

	void load_save(std::array<save::Item, MAX_ITEMS> &save_items) {
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

		control->set_items(decompressed_items);
	}

	std::array<save::Item, MAX_ITEMS> get_save() {
		std::array<save::Item, MAX_ITEMS> compressed_items = {};
		std::vector<Listbox::Item> items = control->get_items();
		uint8_t amount;

		assert(control->get_items().size() <= MAX_ITEMS);

		for (auto i = 0u; i < items.size(); i++) {
			amount = i < items.size() ? items[i].amount : 0;
			compressed_items[i] = save::Item{
				items[i].type,
				amount
			};
		}

		return compressed_items;
	}

	void cleanup() {
		open_state = false;
		delete control;
	}

	void open() {
		open_state = true;
	}

	void close() {
		open_state = false;
		control->cursor_reset();
	}

	bool is_open() {
		return open_state;
	}

	bool add_item(Listbox::Item item) {
		return control->add_item(item);
	}

	std::vector<Listbox::Item> get_items() {
		return control->get_items();
	}

	void draw() {
		control->draw();
	}

	void cursor_up() {
		control->cursor_up();
	}

	void cursor_down() {
		control->cursor_down();
	}

	void cursor_press() {
		control->cursor_press();
	}
}