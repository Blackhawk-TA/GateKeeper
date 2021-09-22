//
// Created by daniel on 22.09.21.
//

#include <sstream>
#include "textbox.hpp"

Textbox::Textbox(std::string text) : Box(rect) {
	Textbox::line_counter = 1;
	Textbox::text = format_text(text);
}

/**
 * Formats a one line string into multiple lines to fit the textbox boundaries
 * @param unformatted_text The unformatted text
 * @return The formatted text with linebreaks
 */
std::string Textbox::format_text(std::string &unformatted_text) {
	std::string output_text;

	if (unformatted_text.length() > LINE_MAX_CHARS) {
		uint8_t char_counter = 0;
		std::string formatted_text;
		std::istringstream iss(unformatted_text);

		for (std::string s; iss >> s;) {
			if (char_counter + s.length() <= LINE_MAX_CHARS) {
				char_counter += s.length() + 1; //Add 1 because of the added space down below
				formatted_text.append(s);
				formatted_text.append(" ");
			} else {
				formatted_text.append("\n");
				formatted_text.append(s);
				char_counter = s.length();
				line_counter++;
			}
		}
		output_text = formatted_text;
	} else {
		output_text = unformatted_text;
	}

	Textbox::line_offset = calculate_line_offset();
	return output_text;
}

/**
 * Calculate the offset to which the text y-position is adjusted to center the text vertically
 * @return The line offset value in pixel
 */
int8_t Textbox::calculate_line_offset() const {
	int8_t offset;

	switch (line_counter) {
		case 1:
			offset = static_cast<int8_t>(font.char_h / 2);
			break;
		case 2:
			offset = 0;
			break;
		case 3:
			offset = static_cast<int8_t>(-font.char_h / 2);
			break;
		default:
			offset = 0;
			break;
	}

	return offset;
}

void Textbox::draw() {
	Box::draw();
	screen.pen = Pen(0, 0, 0, 255);
	screen.text(
		text,
		font,
		Rect(
			PADDING * TILE_SIZE,
			(rect.y + PADDING) * TILE_SIZE + line_offset,
			rect.w * TILE_SIZE,
			rect.h * TILE_SIZE
		)
	);
}

void Textbox::set_text(std::string &new_text) {
	line_counter = 1;
	text = format_text(new_text);
}
