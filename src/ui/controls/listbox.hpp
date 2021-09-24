//
// Created by daniel on 22.09.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "box.hpp"
#include "textbox.hpp"

class Listbox : private Box {
public:
	enum Tooltip {
		SUCCESS = 1,
		FAILURE = 2,
		SUPPRESS = 3
	};

	struct Item {
		std::string name;
		std::string tooltip;
		std::string callback_tooltip;
		std::string callback_fail_tooltip;
		bool single_use;
		uint8_t amount; //Amount 0 indicates menu item
		std::function<Tooltip()> callback;
	};

	explicit Listbox(Rect rect, std::vector<Item> &items);
	~Listbox();
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();
	bool add_item(Listbox::Item &item);

private:
	const uint16_t CURSOR_SPRITE_ID = 1742;
	const uint8_t CURSOR_OFFSET = 1;
	const uint8_t PADDING = 1;
	const Font FONT = minimal_font;
	const uint8_t MAX_ITEMS = 99;
	Rect rect;
	std::vector<Item> items;
	Size spritesheet_size;
	Point cursor_position;
	Textbox *tooltip;

	void update_tooltip();
	void remove_item(uint8_t index);
};
