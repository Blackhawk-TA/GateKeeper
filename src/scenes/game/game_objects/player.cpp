//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include <iostream>
#include "player.hpp"
#include "../../../engine/effects/transition.hpp"
#include "../../../engine/flags.hpp"
#include "handler/game_object_handler.hpp"
#include "../utils/entry_handler.hpp"
#include "../utils/utils.hpp"
#include "handler/extensions/stargate_handler.hpp"
#include "../ui/sidemenu.hpp"
#include "../ui/notification.hpp"

namespace game {
	Player::Player(uint8_t current_save_id) {
		Player::save_id = current_save_id;
		position = get_screen_tiles() / 2;
		spritesheet_size = get_spritesheet_size(characters_spritesheet->bounds);
		elevation_offset = 0;

		//Init properties
		health = MAX_HEALTH;
		level = 1;
		gold = 0;
		cut_scene = false;
		story_state = StoryState::START;

		//Init graphics
		is_animating = true;
		sprite_index = 0;
		current_direction = DOWN;
		animation_sprites = movement_sprites.at(current_direction);
		sprite_id = animation_sprites[sprite_index];
	}

	bool Player::in_action() const {
		return camera::is_moving() || health == 0 || cut_scene || transition::in_process();
	}

	void Player::draw() {
		screen.blit(
			characters_spritesheet,
			Rect((sprite_id % spritesheet_size.w) * TILE_SIZE, (sprite_id / spritesheet_size.h) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
			world_to_screen(position) - Point(0, elevation_offset),
			SpriteTransform::NONE
		);
	}

	void Player::animate() {
		if (camera::is_moving() && !transition::in_process()) {
			//Sprite index increment skips standing sprite because it is already displayed
			sprite_id = animation_sprites[++sprite_index % ANIMATION_SPRITE_COUNT];
		} else {
			sprite_id = animation_sprites[0];
			is_animating = false;
		}
	}

	void Player::take_damage(uint8_t damage_amount) {
		if (health - damage_amount > 0) {
			health -= damage_amount;
		} else {
			health = 0;
			SceneOptions options = {
				save_id,
				CombatData{},
				GameData{
					{},
					health,
					false,
					true,
				},
			};
			load_scene(SceneType::GAMEOVER, options);
		}
	}

	void Player::heal(uint8_t heal_amount) {
		if (health + heal_amount > MAX_HEALTH) {
			health = MAX_HEALTH;
		} else {
			health += heal_amount;
		}
	}

	void Player::move(MovementDirection direction) {
		if (Player::in_action()) return; //Do not move player if already in action

		change_direction(direction); //Change player viewing direction
		Point movement = movements.at(direction);
		Point next_position = camera::get_world_position() + position + movement;

		if (game_objects::check_collisions(next_position)) {
			is_animating = false;
			return;
		}

		//Check if teleport destination is available
		Stargate *destination_gate = stargate_handler::get_destination_gate(next_position);
		if (destination_gate != nullptr) {
			//Trigger teleportation
			uint8_t current_save_id = save_id;
			transition::start([destination_gate, current_save_id, this] {
				gate_teleport(destination_gate, current_save_id);
			});
			return;
		}

		//Move player according to tile flag of next position
		switch (map::get_flag(next_position)) {
			case flags::TileFlags::WALKABLE:
				camera::move(movement);
				elevation_offset = 0;
				break;
			case flags::TileFlags::ELEVATE_1PX:
				camera::move(movement);
				elevation_offset = 1;
				break;
			case flags::TileFlags::ELEVATE_2PX:
				camera::move(movement);
				elevation_offset = 2;
				break;
			case flags::TileFlags::ELEVATE_3PX:
				camera::move(movement);
				elevation_offset = 3;
				break;
			case flags::TileFlags::ENTRY:
				if (entry_handler::enter(next_position, save_id, story_state)) {
					camera::move(movement);
				}
				elevation_offset = 0;
				break;
			case flags::TileFlags::DEADLY:
				camera::move(movement);
				take_damage(health);
				break;
			default:
				is_animating = false;
				return; //Prevent game object state update
		}

		//Start animation timer and directly update sprite animation to prevent delay
		if (!is_animating && camera::is_moving()) {
			is_animating = true;
			sprite_id = animation_sprites[++sprite_index % ANIMATION_SPRITE_COUNT];
		}

		//Update the stargate states when a player comes near them
		game_objects::update_states(next_position);
	}

	void Player::change_direction(MovementDirection direction, bool animate) {
		if (current_direction != direction) {
			animation_sprites = movement_sprites.at(direction);
			current_direction = direction;
			sprite_id = animate ? animation_sprites[1] : animation_sprites[0]; //Set sprite manually to avoid timer delay on player turn
		}
	}

	void Player::gate_teleport(Stargate *destination_gate, uint8_t current_save_id) {
		Point teleport_destination = destination_gate->get_entry_point();
		map::MapSection destination_map_section = destination_gate->get_map_section();
		if (map::get_section() != destination_map_section) {
			utils::teleport_player(destination_map_section, teleport_destination, MovementDirection::DOWN, current_save_id, story_state);
		}

		game_objects::update_states(teleport_destination);
	}

	CharacterData Player::get_character_data() {
		std::vector<GEAR_TYPE> attacks = {};
		auto gears = sidemenu::get_items(sidemenu::MenuType::GEAR);
		attacks.reserve(gears.size());

		for (auto &gear : gears) {
			if (gear.name == "BACK") {
				continue; //Skip sidemenu back entry
			}
			attacks.push_back(static_cast<GEAR_TYPE>(gear.type));
		}

		return CharacterData{
			{},
			CharacterStats{
				1.0,
				attacks,
			},
			movement_sprites.at(LEFT),
			utils::get_attack_sprites(PLAYER),
			health,
			level,
		};
	}

	save::PlayerData Player::get_save() {
		return save::PlayerData{
			health,
			level,
			gold,
			current_direction,
			story_state,
		};
	}

	void Player::load_save(save::PlayerData save_data) {
		health = save_data.health;
		level = save_data.level;
		gold = save_data.gold;

		//Remove gear on first death
		if (save_data.story_state == StoryState::FIRST_DEATH) {
			sidemenu::clear_items(sidemenu::GEAR);
			story_state = StoryState::FIRST_HOSPITAL_WAKEUP;
		} else {
			story_state = save_data.story_state;
		}

		//Set player animation tiles
		if (save_data.direction == NO_DIRECTION) {
			std::cerr << "Invalid player direction, falling back to direction 'DOWN'" << std::endl;
			current_direction = DOWN;
		} else {
			current_direction = save_data.direction;
		}

		//Set player sprite depending on direction
		animation_sprites = movement_sprites.at(current_direction);
		sprite_id = animation_sprites[0];
	}

	MovementDirection Player::get_direction() {
		return current_direction;
	}

	uint8_t Player::get_health() const {
		return health;
	}

	void Player::set_cut_scene(bool value) {
		cut_scene = value;
	}

	bool Player::in_cut_scene() const {
		return cut_scene;
	}

	uint16_t Player::get_gold() const {
		return gold;
	}

	void Player::add_gold(uint16_t amount) {
		if (gold + amount <= MAX_GOLD) {
			gold += amount;
			notification::add_to_queue("+ " + std::to_string(amount) + " Gold");
		} else {
			notification::add_to_queue("+ " + std::to_string(MAX_GOLD - gold) + " Gold");
			gold = MAX_GOLD;
		}

	}

	bool Player::remove_gold(uint16_t amount) {
		if (gold - amount >= 0) {
			gold -= amount;
			notification::add_to_queue("- " + std::to_string(amount) + " Gold");
			return true;
		} else {
			return false;
		}
	}
}
