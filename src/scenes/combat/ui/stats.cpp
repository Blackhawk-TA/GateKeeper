//
// Created by daniel on 26.12.21.
//

#include "stats.hpp"
#include "../characters/template/character.hpp"
#include "../characters/player.hpp"

namespace combat {
	void stats::draw(uint8_t health, uint8_t stamina, uint8_t enemy_health) {
		//Background box
		screen.pen = Pen(0, 0, 0, 150);
		screen.rectangle(Rect(0, 0, 160, 30));

		//Text and Statusbar background
		for (uint8_t i = 0u; i < sizeof(STATUS_BARS) / sizeof(STATUS_BARS[0]); i++) {
			screen.pen = Pen(255, 255, 255, 255);
			screen.text(STATUS_BARS[i], minimal_font, Rect(3, 2 + i * TEXT_DISTANCE, 10, 5), false, TextAlign::left);
			screen.pen = Pen(255, 255, 255, 200);
			screen.rectangle(Rect(50, 4 + i * TEXT_DISTANCE, BAR_LENGTH, 2));
		}

		// Player health
		screen.pen = Pen(0, 255, 0, 255);
		screen.rectangle(Rect(50, 4, int(float(health) / float(Character::MAX_HEALTH) * BAR_LENGTH), 2));

		//Player stamina
		screen.pen = Pen(0, 215, 180, 255);
		screen.rectangle(Rect(50, 4 + TEXT_DISTANCE, int(float(stamina) / float(Player::MAX_STAMINA) * BAR_LENGTH), 2));

		//Enemy health
		screen.pen = Pen(255, 0, 0, 255);
		screen.rectangle(Rect(50, 4 + 2 * TEXT_DISTANCE, int(float(enemy_health) / float(Character::MAX_HEALTH) * BAR_LENGTH), 2));
	}
}