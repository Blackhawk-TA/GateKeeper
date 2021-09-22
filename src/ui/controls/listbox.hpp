//
// Created by daniel on 22.09.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "box.hpp"
#include "textbox.hpp"

class Listbox : private Box {
public:
	struct Item{
		std::string name;
		std::string tooltip;
		std::string callback_tooltip;
		std::function<void()> callback;
	};

	explicit Listbox(Rect rect, std::vector<Item> &items);
	void draw();
	void cursor_up();
	void cursor_down();
	void cursor_press();

private:
	const uint16_t CURSOR_SPRITE_ID = 1742;
	const uint8_t CURSOR_OFFSET = 1;
	const uint8_t PADDING = 1;
	const Font font = minimal_font;
	Rect rect;
	std::vector<Item> items;
	Size spritesheet_size;
	Point cursor_position;
	Textbox *tooltip;

	void update_tooltip();
};
