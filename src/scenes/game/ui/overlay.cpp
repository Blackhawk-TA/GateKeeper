//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../game_objects/handler/player_handler.hpp"
#include "../../../utils/saves/options.hpp"
#include "../../../utils/game_time.hpp"
#include "../game_objects/player.hpp"

using namespace blit;

namespace game::overlay {
	void draw_statusbar() {
		const uint8_t BAR_HEIGHT = 10;
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(0, 0, screen.bounds.w, BAR_HEIGHT));

		screen.pen = Pen(0, 0, 0, 255);
		std::string health_string = "Health: " + std::to_string(player_handler::get_health()) +
			" | Gold: " + std::to_string(player_handler::get_gold()) +
			" | Level: " + std::to_string(player_handler::get_level());
		screen.text(health_string, minimal_font, Rect(3, 1, 10, 10), false, TextAlign::left);

		screen.pen = Pen(155, 155, 155, 200);
		screen.rectangle(Rect(0, BAR_HEIGHT, screen.bounds.w, 2));

		if (player_handler::get_level() != Player::MAX_LEVEL) {
			screen.pen = Pen(0, 255, 0, 200);
			screen.rectangle(Rect(0, BAR_HEIGHT, int(float(player_handler::get_xp()) / float(player_handler::get_next_level_max_xp()) * float(screen.bounds.w)), 2));
		}
	}

	void draw_time() {
		if (!options::show_time) return;

		screen.pen = Pen(255, 255, 255, 100);
		screen.rectangle(Rect(screen.bounds.w - 52, screen.bounds.h - 10, 52, 10));
		screen.pen = Pen(0, 0, 0, 200);
		screen.text(game_time::get_formatted(), minimal_font, Rect(screen.bounds.w - 51, screen.bounds.h - 9, 50, 10), false, TextAlign::right);
	}
}
