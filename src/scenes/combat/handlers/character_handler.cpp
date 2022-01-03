//
// Created by daniel on 30.12.21.
//

#include <iostream>
#include "character_handler.hpp"

namespace combat::character_handler {
	std::vector<Character *> character_collection;
	Timer *animation_timer;
	Player *player;
	Enemy *enemy;

	void init(uint8_t save_id, CombatData combat_data) {
		player = new Player(save_id, combat_data.player);
		enemy = new Enemy(save_id, player, combat_data.enemy);
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

	void next_turn(Character *last_turn) {
		if (last_turn->get_type() == Character::Player) {
			enemy->start_round();
		} else if (last_turn->get_type() == Character::Enemy) {
			player->start_round();
		}
	}

	void draw() {
		//Draw the attacking character above the target so the animation is always shown
		if (player->is_attacking()) {
			enemy->draw();
			player->draw();
		} else {
			player->draw();
			enemy->draw();
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

	bool escape() {
		//TODO save lost health;
		if (blit::random() % 3 == 0) {
			return true;
		} else {
			player->finish_round();
			return false;
		}
	}

		//TODO make generic
	bool attack_light(Character *attacker, Character *target) {
		if (attacker->use_stamina(5)) {
			attacker->animate_attack([target] {
				uint8_t bonus_damage = blit::random() % 10;
				target->take_damage(10 + bonus_damage);
			});
			return true;
		} else {
			attacker->finish_round();
			return false;
		}
	}
}