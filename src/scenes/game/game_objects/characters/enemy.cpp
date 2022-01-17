//
// Created by daniel on 24.11.21.
//

#include "enemy.hpp"
#include <utility>
#include <iostream>
#include "../../player.hpp"
#include "../../../../engine/effects/transition.hpp"
#include "../../utils/utils.hpp"

namespace game {
	Enemy::Enemy(map::MapSection map_section, Point position, CombatCharacterType character_type, MovementDirection direction, uint8_t save_id, bool turn, std::string message)
		: Character(map_section, position, true, false, turn) {
		Enemy::character_type = character_type;
		Enemy::tile_id = get_init_tile_id();
		Enemy::save_id = save_id;
		Enemy::message = std::move(message);
		movement_sprites = {
			{UP, {
				static_cast<uint16_t>(tile_id + 48),
				static_cast<uint16_t>(tile_id + 49),
				static_cast<uint16_t>(tile_id + 50),
				static_cast<uint16_t>(tile_id + 51)
			}},
			{DOWN, {
				tile_id,
				static_cast<uint16_t>(tile_id + 1),
				static_cast<uint16_t>(tile_id + 2),
				static_cast<uint16_t>(tile_id + 3)
			}},
			{LEFT,  {
				static_cast<uint16_t>(tile_id + 16),
				static_cast<uint16_t>(tile_id + 17),
				static_cast<uint16_t>(tile_id + 18),
				static_cast<uint16_t>(tile_id + 19)
			}},
			{RIGHT, {
				static_cast<uint16_t>(tile_id + 32),
				static_cast<uint16_t>(tile_id + 33),
				static_cast<uint16_t>(tile_id + 34),
				static_cast<uint16_t>(tile_id + 35)
			}},
		};

		change_direction(direction, false);
	}

	void Enemy::update(uint32_t time) {
		Character::update(time);

		//Trigger enemy to attack player
		if (!in_action && !Player::in_cut_scene() && !transition::in_process() && player_in_sightline()) {
			in_action = true;
			is_moving = true;
			Player::set_cut_scene(true);
		}

		if (is_moving) {
			walk_to_player();
		}
	}

	void Enemy::trigger_cut_scene() {
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
				Signature{
					static_cast<uint8_t>(map_section),
					static_cast<uint8_t>(position.x),
					static_cast<uint8_t>(position.y),
				},
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
					{MELEE, DAGGER, ARROW, SPEAR},
				};
			case SPIDER:
			case BROWN_BEAR:
			case ICE_BEAR:
				return CharacterStats{
					1.25,
					{MELEE},
				};
			case DEVIL:
			case RED_CREATURE:
				return CharacterStats{
					1.5,
					{MELEE, FIRE}
				};
			default:
				std::cerr << "Invalid CombatCharacterType" << std::endl;
				exit(1);
		}
	}
}
