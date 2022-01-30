//
// Created by daniel on 22.09.21.
//

#include "listbox.hpp"

Listbox::Listbox(Rect rect, std::vector<Item> &items, bool enable_sorting) : Box(rect) {
	Listbox::rect = Box::set_bounds(rect);
	Listbox::items = items;
	Listbox::enable_sorting = enable_sorting;
	view_mode = false;
	cursor_position = Point(rect.x, rect.y + CURSOR_OFFSET);
	confirm_dialog = new ConfirmDialog(Rect(rect.x - 3, 0, 3, 3));
	tooltip = new Textbox();

	update_tooltip();
	sort_list();
}

Listbox::~Listbox() {
	delete tooltip;
	tooltip = nullptr;
	delete confirm_dialog;
	confirm_dialog = nullptr;
}

/**
 * Sorts the list alphabetically, if sorting is enabled
 */
void Listbox::sort_list() {
	if (!enable_sorting) return;

	std::sort(Listbox::items.begin(), Listbox::items.end(), [] (Listbox::Item &item1, Listbox::Item &item2){
		//Move items with the amount 0 to the bottom of the list
		if (item1.amount == 0) { //Move item down in list
			return false;
		} else if (item2.amount == 0) { //Keep position in list
			return true;
		} else {
			return item1.name < item2.name; //Sort alphabetically
		}
	});
}

void Listbox::draw() {
	tooltip->draw();
	confirm_dialog->draw();

	if (view_mode) return;

	Box::draw();
	screen.pen = Pen(0, 0, 0, 255);

	if (items.empty()) {
		//Draw no items text
		screen.text(
			"No items",
			FONT,
			Rect(
				(rect.x + PADDING) * TILE_SIZE,
				static_cast<int>(rect.y + PADDING) * TILE_SIZE + FONT.char_h / 2,
				rect.w * TILE_SIZE,
				TILE_SIZE
			)
		);
	} else {
		//Draw Item names
		std::string item_text;
		for (auto i = 0u; i < items.size(); i++) {
			if (items[i].amount > 0) {
				item_text = std::to_string(items[i].amount) + "x " + items[i].name;
			} else {
				item_text = items[i].name;
			}
			screen.text(
				item_text,
				FONT,
				Rect(
					(rect.x + PADDING) * TILE_SIZE,
					static_cast<int>(rect.y + i + PADDING) * TILE_SIZE + FONT.char_h / 2,
					rect.w * TILE_SIZE,
					TILE_SIZE
				)
			);
		}

		//Draw cursor
		screen.blit_sprite(
			Rect(
				(CURSOR_SPRITE_ID & (spritesheet_size.w - 1)) * TILE_SIZE,
				(CURSOR_SPRITE_ID / spritesheet_size.h) * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE
			),
			world_to_screen(cursor_position),
			SpriteTransform::NONE
		);
	}

}

void Listbox::cursor_reset() {
	cursor_position = Point(rect.x, rect.y + CURSOR_OFFSET);
	confirm_dialog->cursor_reset();
	update_tooltip();
}

void Listbox::cursor_up() {
	if (view_mode) return;

	if (confirm_dialog->is_visible()) {
		confirm_dialog->cursor_up();
	} else if (cursor_position.y - rect.y > 1) {
		cursor_position.y--;
	}

	update_tooltip();
}

void Listbox::cursor_down() {
	if (view_mode) return;

	if (confirm_dialog->is_visible()) {
		confirm_dialog->cursor_down();
	} else if (cursor_position.y - rect.y < static_cast<int>(items.size())) {
		cursor_position.y++;
	}

	update_tooltip();
}

/**
 * Handles a press on a listbox item
 * @return The index of the pressed listbox item
 */
void Listbox::cursor_press(bool set_view_mode) {
	if (view_mode) return;

	uint8_t item_index = cursor_position.y - rect.y - CURSOR_OFFSET;

	if (!items.empty() && item_index < items.size()) {
		if (items[item_index].confirm_dialog) {
			if (confirm_dialog->is_visible()) {
				confirm_dialog->cursor_press([this, item_index, set_view_mode] {
					handle_item_press(item_index, set_view_mode);
				});
			} else {
				confirm_dialog->set_visibility(true);
			}
		} else {
			handle_item_press(item_index, set_view_mode);
		}
	}
}

void Listbox::handle_item_press(uint8_t item_index, bool set_view_mode) {
	std::string callback_tooltip = items[item_index].callback_tooltip;
	std::string callback_fail_tooltip = items[item_index].callback_fail_tooltip;
	Tooltip tooltip_state = items[item_index].callback();

	if (tooltip != nullptr) {
		switch (tooltip_state) {
			case SUCCESS:
				tooltip->set_text(callback_tooltip);
				break;
			case FAILURE:
				tooltip->set_text(callback_fail_tooltip);
				break;
			case SUPPRESS:
				break;
		}
	}

	//Delete items that can only be used once
	if (tooltip_state == Tooltip::SUCCESS && items[item_index].single_use) {
		remove_item(item_index);
	}

	view_mode = set_view_mode;
}

void Listbox::update_tooltip() {
	uint8_t item_index = cursor_position.y - rect.y - CURSOR_OFFSET;
	if (!items.empty() && item_index < items.size()) {
		tooltip->set_text(items[item_index].tooltip);
	}
}

/**
 * Removes item from the list if the amount is more than one, else delete the entire item
 * @param index The index at which the item should be removed
 */
void Listbox::remove_item(uint8_t index) {
	auto it = items.begin();
	bool found = false;
	uint8_t counter = 0;

	while (!found && it != items.end()) {
		if (counter == index) {
			if (it->amount > 1) {
				it->amount--;
			} else {
				it = items.erase(it);
			}
			found = true;
		} else {
			it++;
			counter++;
		}
	}
}

/**
 * Adds either a new item to the list or increments the amount of an existing item if it doesn't exceed the maximum
 * @param item The item that should be added
 * @return True if the item could be added, else false
 */
bool Listbox::add_item(Listbox::Item &item) {
	auto it = items.begin();
	bool found = false;
	bool success = false;

	//Increment amount if item already exists and the amount is lower than the max. allowed
	while (!found && it != items.end()) {
		if (it->name == item.name) {
			if (it->amount < MAX_ITEM_COUNT) {
				it->amount++;
				success = true;
			}
			found = true;
		} else {
			it++;
		}
	}

	//Add item to the end of the list
	if (!found) {
		items.push_back(item);
		sort_list();
		success = true;
	}

	return success;
}

std::vector<Listbox::Item> Listbox::get_items() {
	return items;
}

void Listbox::set_items(std::vector<Item> &new_items) {
	items = new_items;
}

void Listbox::set_view_mode(bool value) {
	view_mode = value;
}
