//
// Created by daniel on 30.12.21.
//

#include "character_handler.hpp"
#include "../ui/attack_menu.hpp"

namespace combat::character_handler {
	std::vector<Character *> character_collection;
	Timer *animation_timer;
	Player *player;
	Enemy *enemy;

	void init(uint8_t save_id, const CombatData& combat_data) {
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
		if (blit::random() % 1 == 0) {
			return true;
		} else {
			player->finish_round();
			return false;
		}
	}

	bool attack(GEAR_TYPE type, Character *attacker, Character *target) {
		std::map<GEAR_TYPE, AttackStats> attacks = {
			{GEAR_SWORD,  AttackStats{10, 10, 10}},
			{GEAR_SPEAR,  AttackStats{15, 15, 15}},
			{GEAR_ARROW,  AttackStats{10, 10, 15}},
			{GEAR_DAGGER, AttackStats{7, 5, 15}},
			{GEAR_FIRE,   AttackStats{30, 30, 10}},
			{GEAR_ICE,    AttackStats{30, 30, 10}},
			{GEAR_SHOCK,  AttackStats{30, 30, 10}},
			{GEAR_MAGIC,  AttackStats{30, 30, 10}},
		};
		AttackStats attack = attacks.at(type);
		float damage_multiplier = attacker->get_stats().damage_multiplier;

		if (attacker->use_stamina(attack.stamina)) {
			attacker->animate_attack(type, [target, attack, damage_multiplier] {
				uint8_t bonus_damage = blit::random() % attack.bonus_damage;
				uint8_t damage = static_cast<uint8_t>(static_cast<float>(attack.base_damage + bonus_damage) * damage_multiplier);
				target->take_damage(damage);
			});
			return true;
		} else {
			attack_menu::set_view_mode(false);
			return false;
		}
	}

	void load_game_scene(uint8_t save_id, bool won, bool finished_game) {
		SceneOptions options = {
			save_id,
			{},
			GameData{
				enemy->get_signature(),
				player->get_health(),
				won,
				finished_game,
			},
			true,
		};

		if (finished_game) {
			load_scene(SceneType::GAMEOVER, options);
		} else {
			load_scene(SceneType::GAME, options);
		}
	}
}