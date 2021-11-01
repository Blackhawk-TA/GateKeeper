//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../../../utils/saves/options.hpp"

using namespace blit;

void overlay::draw_statusbar(uint8_t health) {
	screen.pen = Pen(255, 255, 255, 200);
	screen.rectangle(Rect(0, screen.bounds.h - 10, screen.bounds.w, 10));

	screen.pen = Pen(0, 0, 0, 255);
	std::string health_string = "Health: " + std::to_string(health);
	screen.text(health_string, minimal_font, Rect(screen.bounds.w - 10, screen.bounds.h - 10, 10, 10), false, TextAlign::right);
}
