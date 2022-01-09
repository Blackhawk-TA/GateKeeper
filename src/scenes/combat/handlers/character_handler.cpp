//
// Created by daniel on 30.12.21.
//

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
		if (blit::random() % 3 == 0) {
			return true;
		} else {
			player->finish_round();
			return false;
		}
	}

	bool attack(AttackType type, Character *attacker, Character *target) {
		std::map<AttackType, AttackStats> attacks = {
			{SWORD, AttackStats{10, 10, 10}},
			{SPEAR, AttackStats{15, 15, 15}},
			{ARROW, AttackStats{10, 10, 15}},
			{DAGGER, AttackStats{7, 5, 15}},
			{FIRE, AttackStats{30, 20, 10}},
			{ICE, AttackStats{30, 20, 10}},
			{ELECTRIC, AttackStats{30, 20, 10}},
			{MAGIC, AttackStats{30, 20, 10}},
		};
		AttackStats attack = attacks.at(type);

		if (attacker->use_stamina(attack.stamina)) {
			attacker->animate_attack(type, [target, attack] {
				uint8_t bonus_damage = blit::random() % attack.bonus_damage;
				target->take_damage(attack.base_damage + bonus_damage);
			});
			return true;
		} else {
			attacker->finish_round();
			return false;
		}
	}

	void load_game_scene(uint8_t save_id, bool won) {
		SceneOptions options = {
			save_id,
			{},
			GameData{
				enemy->get_signature(),
				player->get_health(),
				won
			},
			true,
		};
		load_scene(SceneType::GAME, options);
	}
}