//
// Created by daniel on 26.12.21.
//

#include "stats.hpp"
#include "../characters/template/character.hpp"
#include "../characters/player.hpp"

namespace combat {
	void stats::draw(uint8_t health, uint8_t stamina, uint8_t enemy_health) {
		//Background box left
		screen.pen = Pen(0, 0, 0, 150);
		screen.rectangle(Rect(0, BOX_Y_POS, BOX_WIDTH, 22));
		screen.pen = Pen(0, 0, 0, 255);
		screen.text("Enemy Health", minimal_font, Rect(0, BOX_Y_POS - 7, 10, 5), false, TextAlign::left);

		//Enemy health
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(5, BOX_Y_POS + 10, BAR_LENGTH, 2));
		screen.pen = Pen(255, 0, 0, 255);
		screen.rectangle(Rect(5, BOX_Y_POS + 10, int(float(enemy_health) / float(Character::MAX_HEALTH) * BAR_LENGTH), 2));

		//Background box right
		screen.pen = Pen(0, 0, 0, 150);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH, BOX_Y_POS, BOX_WIDTH, 22));
		screen.pen = Pen(0, 0, 0, 255);
		screen.text("Health/Stamina", minimal_font, Rect(screen.bounds.w - BOX_WIDTH, BOX_Y_POS - 7, 10, 5), false, TextAlign::left);

		// Player health
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + 5 , BAR_LENGTH, 2));
		screen.pen = Pen(0, 255, 0, 255);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + 5, int(float(health) / float(Character::MAX_HEALTH) * BAR_LENGTH), 2));

		//Player stamina
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + TEXT_DISTANCE + 5, BAR_LENGTH, 2));
		screen.pen = Pen(0, 215, 180, 255);
		screen.rectangle(Rect(screen.bounds.w - BOX_WIDTH + 5, BOX_Y_POS + TEXT_DISTANCE + 5, int(float(stamina) / float(Player::MAX_STAMINA) * BAR_LENGTH), 2));
	}
}