//
// Created by daniel on 22.09.21.
//

#include <sstream>
#include "textbox.hpp"

Textbox::Textbox(std::string text) : Box(rect) {
	Point screen_tiles = get_screen_tiles();
	Textbox::line_counter = 1;
	Textbox::line_offset = 0;
	Textbox::block_index = 0;
	Textbox::line_max_chars = static_cast<uint8_t>(static_cast<float>(screen_tiles.x) * CHARS_PER_TILE);
	Textbox::block_max_chars = line_max_chars * MAX_LINES - 8; //Minus 8 to compensate for ' ...' at message end and beginning
	Textbox::text_blocks = split_text(text);
	Textbox::text = update_text(block_index);
 }

std::vector<std::string> Textbox::split_text(std::string &unformatted_text) const {
	std::vector<std::string> blocks = {""};
	std::istringstream iss(unformatted_text);
	uint8_t index = 0;

	//Loop over every word in the unformatted text
	for (std::string s; iss >> s;) {
		//If block text length would exceed max chars limiter, go to next block
		if (blocks.at(index).length() + s.length() >= block_max_chars) {
			blocks.at(index).append(" ...");
			index++;
			blocks.emplace_back("... "); //Init new block
		}

		//Add word of unformatted text to block text
		blocks.at(index).append(s + " ");
	}

	return blocks;
}

std::string Textbox::format_text(std::string &unformatted_text) {
	std::string output_text;
	line_counter = 1;

	if (unformatted_text.length() > line_max_chars) {
		uint8_t char_counter = 0;
		std::string formatted_text;
		std::istringstream iss(unformatted_text);

		for (std::string s; iss >> s;) {
			if (char_counter + s.length() <= line_max_chars) {
				char_counter += s.length() + 1; //Add 1 because of the added space down below
				formatted_text.append(s);
				formatted_text.append(" ");
			} else {
				formatted_text.append("\n");
				formatted_text.append(s);
				formatted_text.append(" ");
				char_counter = s.length() + 1;
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

int8_t Textbox::calculate_line_offset() const {
	int8_t offset;

	switch (line_counter) {
		case 1:
			offset = static_cast<int8_t>(font.char_h / 2);
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
			(Box::rect.y + PADDING) * TILE_SIZE + line_offset,
			Box::rect.w * TILE_SIZE,
			Box::rect.h * TILE_SIZE
		)
	);

	if (block_index < text_blocks.size() - 1) {
		screen.blit(
			screen.sprites,
			Rect(
				(NEXT_TEXTBOX_TILE_ID & (spritesheet_size.w - 1)) * TILE_SIZE,
				(NEXT_TEXTBOX_TILE_ID / spritesheet_size.h) * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE
			),
			Point((Box::rect.x + Box::rect.w - 1) * TILE_SIZE, (Box::rect.y + Box::rect.h - 1) * TILE_SIZE)
		);
	}
}

void Textbox::set_text(std::string &new_text) {
	block_index = 0;
	text_blocks = split_text(new_text);
	text = update_text(block_index);
}

bool Textbox::next() {
	block_index++;
	if (block_index < text_blocks.size()) {
		text = update_text(block_index);
		return true;
	}

	return false;
}

std::string Textbox::update_text(uint8_t index) {
	return format_text(text_blocks.at(index));
}
