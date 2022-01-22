//
// Created by daniel on 22.09.21.
//

#pragma once
#include "box.hpp"

class Textbox : public Box {
private:
	static constexpr Rect rect = Rect(0, 12, 20, 3);
	const uint8_t PADDING = 1; //Distance between Box border and text in tiles
	const uint8_t MAX_LINES = 2;
	const uint16_t NEXT_TEXTBOX_TILE_ID = 1806;
	const Font font = minimal_font;
	const float CHARS_PER_TILE = 2.8;
	uint8_t line_max_chars;
	uint8_t block_max_chars;
	uint8_t block_index;
	int8_t line_offset;
	uint8_t line_counter;
	std::string text;
	std::vector<std::string>text_blocks; //Each text block is shown in its own textbox

	/**
	 * Formats a one line string into multiple lines to fit the textbox boundaries
	 * @param unformatted_text The unformatted text
	 * @return The formatted text with linebreaks
	 */
	std::string format_text(std::string &unformatted_text);

	/**
	 * Splits the given unformatted text into blocks. Each block is shown in its own textbox
	 * @param unformatted_text The unformatted text that is split into blocks
	 */
	std::vector<std::string> split_text(std::string &unformatted_text);

	/**
	 * Calculate the offset to which the text y-position is adjusted to center the text vertically
	 * @return The line offset value in pixel
	 */
	int8_t calculate_line_offset() const;

	/**
	 * Updates the textboxes text to the text block with the given index
	 * @param index The index of the text block
	 * @return The formatted text of the text block
	 */
	std::string update_text(uint8_t index);

public:
	explicit Textbox(std::string text = "");
	~Textbox() override = default;

	/**
	 * Draws the textbox on the screen
	 */
	void draw() override;

	/**
	 * Sets the text of the current textbox and splits it into several text blocks if it is too long
	 * @param new_text The new text of the texbox
	 */
	void set_text(std::string &new_text);

	/**
	 * Shows the next textbox if the text is too long for one.
	 * @return True if the next textbox is shown, else false
	 */
	bool next();
};
