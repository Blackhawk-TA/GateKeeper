//
// Created by daniel on 24.11.21.
//

#include "enemy.hpp"
#include <utility>
#include <iostream>
#include "../player.hpp"
#include "../../../../engine/effects/transition.hpp"
#include "../../utils/utils.hpp"

namespace game {
	Enemy::Enemy(map::MapSection map_section, Point position, CombatCharacterType character_type, MovementDirection direction, uint8_t save_id, bool turn, std::string message)
		: Character(map_section, position, true, false, turn) {
		Enemy::character_type = character_type;
		Enemy::tile_id = get_init_tile_id();
		Enemy::save_id = save_id;
		Enemy::message = std::move(message);
		set_movement_sprites();
		change_direction(direction, false);
	}

	void Enemy::update(uint32_t time) {
		Character::update(time);

		//Trigger enemy to attack player
		if (!in_action && !Player::in_cut_scene() && !transition::in_process() && player_in_sightline()) {
			turn = false;
			in_action = true;
			moving_to_player = true;
			Player::set_cut_scene(true);
		}

		if (moving_to_player) {
			walk_to_player();
		}
	}

	void Enemy::trigger_cutscene() {
		Character::player_face_character();
		start_interaction();
	}

	bool Enemy::player_interact() {
		if (Character::player_interact()) {
			in_action = true;
			Player::set_cut_scene(true);
			start_interaction();
			return true;
		}
		return false;
	}

	void Enemy::start_interaction() {
		if (!message.empty()) {
			textbox = new Textbox(message);
		} else {
			start_fight();
		}
	}

	void Enemy::close_textbox() {
		GameObject::close_textbox();
		start_fight();
	}

	void Enemy::start_fight() {
		CombatData combat_data = {
			map_section,
			Player::get_character_data(),
			CharacterData{
				signature,
				get_stats(),
				movement_sprites.at(RIGHT),
				utils::get_attack_sprites(character_type),
				0,
				0,
			}
		};
		SceneOptions options = {
			save_id,
			combat_data,
			{},
			true,
		};
		load_scene(SceneType::COMBAT, options);
	}

	void Enemy::set_state(uint8_t new_state) {}
	void Enemy::update_state(Point next_position) {}

	uint16_t Enemy::get_init_tile_id() {
		switch (character_type) {
			case PLAYER:
				return 64;
			case BLUE_GUARD:
				return 76;
			case SPIDER:
				return 72;
			case BROWN_BEAR:
				return 192;
			case ICE_BEAR:
				return 204;
			case DEVIL:
				return 196;
			case RED_CREATURE:
				return 200;
			default:
				std::cerr << "Invalid CombatCharacterType" << std::endl;
				exit(1);
		}
	}

	CharacterStats Enemy::get_stats() {
		switch (character_type) {
			case BLUE_GUARD:
				return CharacterStats{
					1.0,
					{GEAR_SWORD, GEAR_DAGGER, GEAR_ARROW, GEAR_SPEAR},
				};
			case SPIDER:
			case BROWN_BEAR:
			case ICE_BEAR:
				return CharacterStats{
					1.25,
					{GEAR_SWORD},
				};
			case DEVIL:
			case RED_CREATURE:
				return CharacterStats{
					1.5,
					{GEAR_SWORD, GEAR_FIRE}
				};
			default:
				std::cerr << "Invalid CombatCharacterType" << std::endl;
				exit(1);
		}
	}
}
