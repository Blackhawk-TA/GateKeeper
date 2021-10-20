//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../utils/saves/options.hpp"

using namespace blit;

void overlay::draw_fps(uint32_t &ms_start, uint32_t &ms_end) {
	//Abort if fps counter is hidden
	if (!options::show_fps) return;

	//Draw fps box
	screen.alpha = 255;
	screen.pen = Pen(255, 255, 255, 100);
	screen.rectangle(Rect(1, screen.bounds.h - 10, 20, 9));
	screen.pen = Pen(0, 0, 0, 200);

	//Calculate frames per second (fps)
	float time_difference_in_sec = static_cast<float>(ms_end - ms_start) / 1000;
	if (time_difference_in_sec == 0) {
		time_difference_in_sec = 1;
	}
	int fps = static_cast<int>(1 / time_difference_in_sec);

	//Cap max shown fps
	if (fps > 999) {
		fps = 999;
	}

	//Draw fps counter
	std::string fms = std::to_string(fps);
	screen.text(fms, minimal_font, Rect(3, screen.bounds.h - 9, 10, 16));

	//Draw frame time boxes
	int block_size = 4;
	for (int i = 0; i < static_cast<int>(ms_end - ms_start); i++) {
		screen.pen = Pen(i * 5, 255 - (i * 5), 0);
		screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
	}
}
