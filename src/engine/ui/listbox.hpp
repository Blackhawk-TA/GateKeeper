//
// Created by daniel on 22.09.21.
//

#pragma once
#include "box.hpp"
#include "textbox.hpp"
#include "confirm_dialog.hpp"

class Listbox : public Box {
public:
	enum Tooltip {
		SUCCESS = 1,
		FAILURE = 2,
		SUPPRESS = 3
	};

	struct Item {
		uint8_t type;
		std::string name;
		std::string tooltip;
		std::string callback_tooltip;
		std::string callback_fail_tooltip;
		bool single_use;
		uint8_t amount; //Amount 0 indicates menu item
		std::function<Tooltip()> callback;
		bool confirm_dialog = false;
		bool sort_to_bottom = false;
	};

	explicit Listbox(Rect rect, std::vector<Item> &items, bool enable_sorting = true);
	~Listbox() override;
	void draw() override;
	void set_view_mode(bool value);
	void cursor_reset();
	void cursor_up();
	void cursor_down();
	void cursor_press(bool set_view_mode = false);
	bool add_item(Item &item);
	void update_tooltip();
	void set_items(std::vector<Item> &new_items);
	std::vector<Item> get_items();

protected:
	std::vector<Item> items;

private:
	const uint16_t CURSOR_SPRITE_ID = 1742;
	const uint8_t CURSOR_OFFSET = 1;
	const uint8_t PADDING = 1;
	const Font FONT = minimal_font;
	const uint8_t MAX_ITEM_COUNT = 99;
	bool enable_sorting;
	bool view_mode;
	Point cursor_position;
	Textbox *tooltip;
	ConfirmDialog *confirm_dialog;

	void sort_list();
	void remove_item(uint8_t index);
	void handle_item_press(uint8_t item_index, bool set_view_mode);
};
