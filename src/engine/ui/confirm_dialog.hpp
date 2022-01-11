//
// Created by D069765 on 11.01.2022.
//

#pragma once
#include "box.hpp"

class ConfirmDialog : public Box {
public:
	explicit ConfirmDialog(Rect rect);
	~ConfirmDialog() = default;
	void draw() override;
	void cursor_reset();
	void cursor_up();
	void cursor_down();
	void cursor_press(const std::function<void()>& callback);

private:
	const uint8_t PADDING = 1; //Distance between Box border and text in tiles
	const uint8_t HALF_PADDING_PX = 8;
	const uint16_t CURSOR_SPRITE_ID = 1742;
	const Font FONT = minimal_font;
	const std::array<std::string, 2> confirm_options = { "YES", "NO" };

	Rect rect;
	Point cursor_position;
};
