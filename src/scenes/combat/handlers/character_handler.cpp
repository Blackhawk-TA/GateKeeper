//
// Created by daniel on 30.12.21.
//

#include "character_handler.hpp"
#include "../characters/enemy.hpp"
#include "../characters/player.hpp"

namespace combat::character_handler {
	std::vector<Character *> character_collection;
	Timer *animation_timer;

	void init(CombatData combat_data) {
		character_collection.emplace_back(new Enemy(combat_data.enemy));
		character_collection.emplace_back(new Player(combat_data.player));

		animation_timer = new Timer();
		animation_timer->init(animate, 175, -1);
		animation_timer->start();
	}

	void cleanup() {
		for (auto &character : character_collection) {
			delete character;
			character = nullptr;
		}

		character_collection.clear();
	}

	void draw() {
		for (auto &character : character_collection) {
			character->draw();
		}
	}

	void update(uint32_t time) {
		for (auto &character : character_collection) {
			character->update(time);
		}
	}

	void animate(Timer &timer) {
		for (auto &character : character_collection) {
			character->animate(timer);
		}
	}
}