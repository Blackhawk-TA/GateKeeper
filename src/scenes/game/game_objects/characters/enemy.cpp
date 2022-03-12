//
// Created by daniel on 24.11.21.
//

#include "enemy.hpp"
#include <utility>
#include <iostream>
#include "../../../../engine/effects/transition.hpp"
#include "../../utils/utils.hpp"
#include "../handler/player_handler.hpp"

namespace game {
	Enemy::Enemy(map::MapSection map_section, Point position, CombatCharacterType character_type, MovementDirection direction, uint8_t save_id, bool turn, std::string message, bool can_respawn)
		: Character(map_section, position, true, false, turn) {
		Enemy::character_type = character_type;
		Enemy::tile_id = get_init_tile_id();
		Enemy::save_id = save_id;
		Enemy::can_respawn = can_respawn;
		Enemy::message = std::move(message);
		set_movement_sprites();
		change_direction(direction, false);
	}

	void Enemy::update(uint32_t time) {
		Character::update(time);

		//Trigger enemy to attack player
		if (!in_action && !player_handler::in_cut_scene() && !transition::in_process() && player_in_sightline()) {
			turn = false;
			in_action = true;
			moving_to_player = true;
			player_handler::set_cut_scene(true);
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
			player_handler::set_cut_scene(true);
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
			player_handler::get_character_data(),
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

	uint16_t Enemy::get_init_tile_id() {
		switch (character_type) {
			case PLAYER:
				return 16;
			case BLUE_GUARD:
				return 28;
			case SPIDER:
				return 24;
			case BROWN_BEAR:
				return 144;
			case ICE_BEAR:
				return 156;
			case DEVIL:
				return 148;
			case RED_CREATURE:
				return 152;
			case RED_GUARD:
				return 256;
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

	GameObject::ObjectType Enemy::get_type() {
		return EnemyType;
	}

	void Enemy::set_active(bool active) {
		if (active && !can_respawn) {
			return;
		}

		GameObject::set_active(active);
	}

	bool Enemy::can_be_respawned() const {
		return can_respawn;
	}
}
