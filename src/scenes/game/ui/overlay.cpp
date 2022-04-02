//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../game_objects/handler/player_handler.hpp"

using namespace blit;

namespace game::overlay {
	void draw_statusbar() {
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(0, 0, screen.bounds.w, 10));

		screen.pen = Pen(0, 0, 0, 255);
		std::string health_string = "Health: " + std::to_string(player_handler::get_health()) + " | Gold: " + std::to_string(player_handler::get_gold());
		screen.text(health_string, minimal_font, Rect(3, 1, 10, 10), false, TextAlign::left);
	}
}
