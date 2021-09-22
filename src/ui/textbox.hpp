//
// Created by daniel on 22.09.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "box.hpp"

class Textbox : private Box {
private:
	static constexpr Rect rect = Rect(0, 12, 20, 3);
	const uint8_t PADDING = 1; //Distance between Box border and text in tiles
	const uint8_t LINE_MAX_CHARS = 57; //Maximum amount of chars per line
	const Font font = minimal_font;
	int8_t line_offset;
	uint8_t line_counter;
	std::string text;

	std::string format_text(std::string &unformatted_text);
	int8_t calculate_line_offset() const;

public:
	explicit Textbox(std::string &text);
	void draw();
};
