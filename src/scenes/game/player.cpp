//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include <iostream>
#include "player.hpp"
#include "../../engine/effects/transition.hpp"
#include "../../engine/flags.hpp"
#include "handlers/game_objects/game_object_handler.hpp"
#include "handlers/entry_handler.hpp"
#include "handlers/game_objects/extensions/stargate_handler.hpp"
#include "utils/utils.hpp"

namespace game {
	bool Player::cut_scene = false;
	bool Player::dead = false;
	uint16_t Player::sprite_id = 0;
	uint8_t Player::sprite_index = 0;
	uint8_t Player::health = MAX_HEALTH;
	uint8_t Player::level = 1;
	uint8_t Player::save_id = 0;
	MovementDirection Player::current_direction = DOWN;
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> Player::animation_sprites;
	std::vector<AttackType> Player::attacks = {};
	const std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> Player::movement_sprites = {
		{UP,    {112, 113, 114, 115}},
		{DOWN,  {64,  65,  66,  67}},
		{LEFT,  {80,  81,  82,  83}},
		{RIGHT, {96,  97,  98,  99}}
	};

	Player::Player(save::PlayerData player_data, uint8_t current_save_id) {
		Player::save_id = current_save_id;
		position = get_screen_tiles() / 2;
		spritesheet_size = get_spritesheet_size(characters_spritesheet->bounds);
		elevation_offset = 0;

		//Set static vars in case of re-initialisation
		cut_scene = false;
		dead = false;

		health = player_data.health;
		level = player_data.level;
		current_direction = player_data.direction;

		//Parse available attacks from player_data to local variable
		attacks = {};
		for (auto & attack : player_data.attacks) {
			if (attack == AttackType::NO_ATTACK) break;
			attacks.push_back(attack);
		}

		//Set player animation tiles
		if (player_data.direction == NO_DIRECTION) {
			std::cerr << "Invalid player direction, falling back to direction 'DOWN'" << std::endl;
			current_direction = DOWN;
		} else {
			current_direction = player_data.direction;
		}
		animation_sprites = movement_sprites.at(current_direction);
		sprite_id = animation_sprites[0];
		sprite_index = 0;

		animation_timer.init(animate, 175, -1);
	}

	bool Player::in_action() {
		return camera::is_moving() || dead || cut_scene || transition::in_process();
	}

	void Player::animate(Timer &timer) {
		if (camera::is_moving() && !transition::in_process()) {
			//Sprite index increment skips standing sprite because it is already displayed
			sprite_id = animation_sprites[++sprite_index % ANIMATION_SPRITE_COUNT];
		} else {
			sprite_id = animation_sprites[0];
			timer.stop();
		}
	}

	void Player::take_damage(uint8_t damage_amount) {
		if (health - damage_amount > 0) {
			health -= damage_amount;
		} else {
			dead = true;
			SceneOptions options = {
				save_id,
			};
			load_scene(GAMEOVER, options);
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
			stop_animation();
			return;
		}

		//Check if teleport destination is available
		Stargate *destination_gate = stargate_handler::get_destination_gate(next_position);
		if (destination_gate != nullptr) {
			//Trigger teleportation
			uint8_t current_save_id = save_id;
			transition::start([destination_gate, current_save_id] {
				gate_teleport(destination_gate, current_save_id);
			});
			return;
		}

		//Start animation timer and directly update sprite animation to prevent delay
		if (!animation_timer.is_running()) {
			animation_timer.start();
			sprite_id = animation_sprites[++sprite_index % ANIMATION_SPRITE_COUNT];
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
				if (entry_handler::enter(next_position, save_id)) {
					camera::move(movement);
				}
				elevation_offset = 0;
				break;
			case flags::TileFlags::DEADLY:
				camera::move(movement);
				take_damage(health);
				break;
			default:
				stop_animation();
				return; //Prevent game object state update
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

	void Player::draw() {
		screen.blit(
			characters_spritesheet,
			Rect((sprite_id % spritesheet_size.w) * TILE_SIZE, (sprite_id / spritesheet_size.h) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
			world_to_screen(position) - Point(0, elevation_offset),
			SpriteTransform::NONE
		);
	}

	/**
	 * Teleports a player to the given gate and sets the movement direction to facing downwards
	 * @param destination_gate The gate to which the player is teleported
	 * @param current_save_id The id of the current save
	 */
	void Player::gate_teleport(Stargate *destination_gate, uint8_t current_save_id) {
		Point teleport_destination = destination_gate->get_entry_point();
		map::MapSection destination_map_section = destination_gate->get_map_section();
		if (map::get_section() != destination_map_section) {
			utils::teleport_player(destination_map_section, teleport_destination, MovementDirection::DOWN, current_save_id);
		}

		game_objects::update_states(teleport_destination);
	}

	MovementDirection Player::get_direction() {
		return current_direction;
	}

	void Player::stop_animation() {
		animation_timer.stop();
		sprite_id = animation_sprites[0];
	}

	uint8_t Player::get_health() {
		return health;
	}

	void Player::set_cut_scene(bool value) {
		cut_scene = value;
	}

	bool Player::in_cut_scene() {
		return cut_scene;
	}

	CharacterData Player::get_character_data() {
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
		std::array<AttackType, MAX_ATTACKS> attacks_array = {};

		for (uint8_t i = 0u; i < attacks.size(); i++) {
			attacks_array[i] = attacks.at(i);
		}

		return save::PlayerData{
			health,
			level,
			current_direction,
			attacks_array,
		};
	}

	bool Player::is_dead() {
		return dead;
	}
}
