//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../utils/saves/options.hpp"

using namespace blit;

void overlay::draw_statusbar(uint8_t health) {
	screen.pen = Pen(255, 255, 255, 200);
	screen.rectangle(Rect(0, screen.bounds.h - 10, screen.bounds.w, 10));

	screen.pen = Pen(0, 0, 0, 255);
	std::string health_string = "Health: " + std::to_string(health);
	screen.text(health_string, minimal_font, Rect(screen.bounds.w - 10, screen.bounds.h - 10, 10, 10), false, TextAlign::right);
}

void overlay::draw_fps(uint32_t &ms_start, uint32_t &ms_end) {
	//Abort if fps counter is hidden
	if (!options::show_fps) return;

	//Draw fps box
	screen.alpha = 255;
	screen.pen = Pen(255, 255, 255, 100);
	screen.rectangle(Rect(0, screen.bounds.h - 10, 20, 10));
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
	std::string fps_string = std::to_string(fps);
	screen.text(fps_string, minimal_font, Rect(1, screen.bounds.h - 10, 10, 10));

	//Draw frame time boxes
	int block_size = 4;
	for (int i = 0; i < static_cast<int>(ms_end - ms_start); i++) {
		screen.pen = Pen(i * 5, 255 - (i * 5), 0);
		screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
	}
}
