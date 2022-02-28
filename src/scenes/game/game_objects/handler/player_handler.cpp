//
// Created by daniel on 28.02.22.
//

#include "player_handler.hpp"
#include "../player.hpp"

namespace game::player_handler {
	Player *player;
	Timer *animation_timer;

	void init(uint8_t save_id) {
		player = new Player(save_id);

		animation_timer = new Timer();
		animation_timer->init(animate, 150, -1);
		animation_timer->start();
	}

	void cleanup() {
		delete player;
		player = nullptr;

		delete animation_timer;
		animation_timer = nullptr;
	}

	void draw() {
		player->draw();
	}

	void animate(Timer &timer) {
		player->animate();
	}

	void move(MovementDirection direction) {
		player->move(direction);
	}

	uint8_t get_health() {
		return player->get_health();
	}

	void heal(uint8_t heal_amount) {
		player->heal(heal_amount);
	}

	MovementDirection get_direction() {
		return player->get_direction();
	}

	void change_direction(MovementDirection direction, bool animate) {
		player->change_direction(direction, animate);
	}

	void set_cut_scene(bool value) {
		player->set_cut_scene(value);
	}

	bool in_cut_scene() {
		return player->in_cut_scene();
	}

	bool is_dead() {
		return  player->is_dead();
	}

	CharacterData get_character_data() {
		return player->get_character_data();
	}

	save::PlayerData get_save() {
		return player->get_save();
	}

	void load_save(save::PlayerData save_data) {
		player->load_save(save_data);
	}
}
