//
// Created by Daniel Peters on 12.04.21.
//

#include "overlay.hpp"
#include "../game_objects/handler/player_handler.hpp"
#include "../../../utils/game_time.hpp"

using namespace blit;

namespace game::overlay {
	uint32_t save_time = 0;

	void draw_statusbar() {
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(0, 0, screen.bounds.w, 10));

		screen.pen = Pen(0, 0, 0, 255);
		std::string health_string = "Health: " + std::to_string(player_handler::get_health()) + " | Gold: " + std::to_string(player_handler::get_gold());
		screen.text(health_string, minimal_font, Rect(3, 1, 10, 10), false, TextAlign::left);
	}

	void draw_save_icon() {
		if (save_time == 0 || game_time::get_time() > save_time + 2000) { //Show icon for 2s only
			return;
		}

		uint16_t icon_id = 1761;
		Size spritesheet_size = get_spritesheet_size(screen.sprites->bounds);

		screen.blit(
			screen.sprites,
			Rect(
				(icon_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(icon_id / spritesheet_size.h) * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE
				),
			 Point(0, 11)
		);
	}
}