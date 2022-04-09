//
// Created by daniel on 26.12.21.
//

#include "stats.hpp"
#include "../characters/template/character.hpp"
#include "../characters/player.hpp"

namespace combat::stats {
	void draw_player_stats(uint8_t health, uint8_t max_health, uint8_t stamina, uint8_t level) {
		//Background box right
		screen.pen = Pen(0, 0, 0, 150);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH, BOX_Y_POS, BOX_WIDTH, 32));
		screen.pen = Pen(255, 255, 255, 255);
		screen.text("Health/Stamina (" + std::to_string(level) + ")", minimal_font, Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + 4, 10, 5), false, TextAlign::left);

		// Player health
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + 15 , BAR_LENGTH, 2));
		screen.pen = Pen(0, 255, 0, 255);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + 15, int(float(health) / float(max_health) * BAR_LENGTH), 2));

		//Player stamina
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + TEXT_DISTANCE + 15, BAR_LENGTH, 2));
		screen.pen = Pen(0, 215, 180, 255);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + TEXT_DISTANCE + 15, int(float(stamina) / float(Player::MAX_STAMINA) * BAR_LENGTH), 2));
	}

	void draw_enemy_stats(uint8_t health, uint8_t max_health, uint8_t level) {
		//Background box left
		screen.pen = Pen(0, 0, 0, 150);
		screen.rectangle(Rect(0, BOX_Y_POS, BOX_WIDTH, 32));
		screen.pen = Pen(255, 255, 255, 255);
		screen.text("Enemy Health (" + std::to_string(level) + ")", minimal_font, Rect(5, BOX_Y_POS + 4, 10, 5), false, TextAlign::left);

		//Enemy health
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(5, BOX_Y_POS + 20, BAR_LENGTH, 2));
		screen.pen = Pen(255, 0, 0, 255);
		screen.rectangle(Rect(5, BOX_Y_POS + 20, int(float(health) / float(max_health) * BAR_LENGTH), 2));
	}
}