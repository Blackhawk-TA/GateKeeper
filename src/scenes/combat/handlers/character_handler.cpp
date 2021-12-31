//
// Created by daniel on 30.12.21.
//

#include "character_handler.hpp"
#include "../characters/enemy.hpp"
#include "../characters/player.hpp"

namespace combat::character_handler {
	std::vector<Character *> character_collection;
	Timer *animation_timer;
	Player *player;
	Enemy *enemy;

	void init(CombatData combat_data) {
		player = new Player(combat_data.player);
		enemy = new Enemy(combat_data.enemy);
		character_collection.push_back(player);
		character_collection.push_back(enemy);

		animation_timer = new Timer();
		animation_timer->init(animate, 175, -1);
		animation_timer->start();
	}

	void cleanup() {
		animation_timer->stop();
		delete animation_timer;

		for (auto &character : character_collection) {
			delete character;
			character = nullptr;
		}

		character_collection.clear();
	}

	Player *get_player() {
		return player;
	}

	Enemy *get_enemy() {
		return enemy;
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