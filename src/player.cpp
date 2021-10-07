//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include <iostream>
#include "player.hpp"
#include "handlers/entry_handler.hpp"
#include "engine/transition.hpp"
#include "engine/flags.hpp"
#include "handlers/stargate_handler.hpp"

bool Player::is_moving = false;
bool Player::is_attacking = false;
bool Player::is_evading = false;

Player::MovementDirection Player::current_direction;

Vec2 Player::evasion_position_modifier;
float Player::evasion_modifier = 0;

Timer *Player::animation_timer;
Timer *Player::action_timer;

uint16_t Player::sprite_id = 0;
uint8_t Player::sprite_index = 0;

std::array<uint16_t, Player::ANIMATION_SPRITE_COUNT> Player::animation_sprites;
const std::map<Player::MovementDirection, std::array<uint16_t, Player::ANIMATION_SPRITE_COUNT>> Player::movement_sprites = {
	{UP,    {118, 119, 120, 121}},
	{DOWN,  {70,  71,  72,  73}},
	{LEFT,  {102, 103, 104, 105}},
	{RIGHT, {86,  87,  88,  89}}
};

Player::Player(MovementDirection direction) {
	Player::position = get_screen_tiles() / 2;
	Player::characters = Surface::load(asset_characters);
	Player::player_attack = Surface::load(asset_player_attack);
	Player::spritesheet_size = get_spritesheet_size(Player::characters->bounds);
	Player::attack_spritesheet_size = get_spritesheet_size(Player::player_attack->bounds);

	//Set player animation tiles
	Player::current_direction = direction;
	Player::animation_sprites = movement_sprites.at(Player::current_direction);
	Player::sprite_id = animation_sprites[0];

	animation_timer = new Timer();
	animation_timer->init(animate, 175, -1);
	action_timer = new Timer();
	action_timer->init(animate_action, 75, ANIMATION_SPRITE_COUNT + 1);
}

bool Player::in_action() {
	return is_moving || is_evading || is_attacking || transition::in_progress();
}

void Player::animate(Timer &timer) {
	if ((is_moving || camera::is_moving()) && !transition::in_progress()) {
		sprite_index++; //Skips standing sprite because it is already displayed
		sprite_id = animation_sprites[sprite_index % ANIMATION_SPRITE_COUNT];
	} else {
		sprite_id = animation_sprites[0];
		animation_timer->stop();
	}
}

void Player::animate_action(Timer &timer) {
	if (timer.loop_count <= ANIMATION_SPRITE_COUNT) {
		if (is_attacking) {
			sprite_id = animation_sprites[sprite_index % ANIMATION_SPRITE_COUNT];
			sprite_index++;
		} else if (is_evading) {
			if (timer.loop_count <= ANIMATION_SPRITE_COUNT / 2) {
				evasion_modifier -= 0.25f;
			} else {
				evasion_modifier += 0.25f;
			}

			switch (current_direction) {
				case UP:
					evasion_position_modifier = Vec2(0, -evasion_modifier);
					break;
				case DOWN:
					evasion_position_modifier = Vec2(0, evasion_modifier);
					break;
				case LEFT:
					evasion_position_modifier = Vec2(-evasion_modifier, 0);
					break;
				case RIGHT:
					evasion_position_modifier = Vec2(evasion_modifier, 0);
					break;
			}

			sprite_index--;
			sprite_id = animation_sprites[sprite_index % ANIMATION_SPRITE_COUNT];
		}
	} else {
		animation_sprites = movement_sprites.at(current_direction);
		sprite_id = animation_sprites[0];
		sprite_index = 0;
		is_attacking = false;
		is_evading = false;
		timer.stop();
	}
}

void Player::attack() {
	if (!Player::in_action()) {
		animation_sprites = attack_sprites.at(current_direction);
		sprite_id = animation_sprites[0];
		sprite_index = 0;
		is_attacking = true;
		if (!action_timer->is_running()) {
			action_timer->start();
		}
	}
}

//TODO check here if player bumps backwards into wall
void Player::evade() {
	if (!Player::in_action()) {
		action_timer->start();
		evasion_modifier = 0;
		evasion_position_modifier = Vec2(0, 0);
		sprite_index = ANIMATION_SPRITE_COUNT;
		is_evading = true;
	}
}

void Player::stop_movement() {
	is_moving = false;
}

void Player::move(MovementDirection direction) {
	//Do not move when a transition is in progress
	if (transition::in_progress()) {
		return;
	}

	Point movement = movements.at(direction);
	is_moving = true;

	//Do not trigger a movement while another one is in progress
	if (camera::is_moving() || is_attacking || is_evading) {
		return;
	}

	//Start animation timer if not already running
	if (!animation_timer->is_running()) {
		animation_timer->start();
	}

	//Set player sprite direction
	set_direction(direction);

	//Move player according to tile flag of next position
	Point next_position = camera::get_world_position() + position + movement;
	uint8_t entry_id;

	if (stargate_handler::check_collisions(next_position)) {
		is_moving = false;
		return;
	}

	//Check if teleport destination is available
	Stargate *destination_gate = stargate_handler::get_destination_gate(next_position);
	if (destination_gate != nullptr) {
		//Trigger teleportation
		transition::start([destination_gate, this] {
			gate_teleport(destination_gate);
		});
		is_moving = false;
		return;
	}

	//Update the stargate states when a player comes near them
	stargate_handler::update_states(next_position);

	switch (map::get_flag(next_position)) {
		case flags::TileFlags::WALKABLE:
			camera::move(movement);
			break;
		case flags::TileFlags::ENTRY:
			entry_id = entry_handler::get_id(next_position, map::get_section());

			//No entry found, stop movement
			if (entry_id == 255) {
				is_moving = false;
				return;
			}

			//Teleport to position on different tile map
			transition::start([entry_id, next_position] {
				entry_handler::teleport(entry_id, next_position);
			});
			camera::move(movement);
			break;
		default:
			is_moving = false;
	}
}

void Player::set_direction(MovementDirection direction) {
	if (current_direction != direction) {
		animation_sprites = movement_sprites.at(direction);
		current_direction = direction;
		sprite_id = animation_sprites[0]; //Set sprite manually to avoid timer delay on player turn
	}
}

void Player::draw() {
	if (is_attacking) {
		screen.blit(
			player_attack,
			Rect((sprite_id % attack_spritesheet_size.w) * TILE_SIZE, (sprite_id / attack_spritesheet_size.h) * TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE),
			world_to_screen(position - Point(1,1)),
			SpriteTransform::NONE
		);
	} else {
		screen.blit(
			characters,
			Rect((sprite_id % spritesheet_size.w) * TILE_SIZE, (sprite_id / spritesheet_size.h) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
			world_to_screen(position) + world_to_screen(evasion_position_modifier),
			SpriteTransform::NONE
		);
	}
}

/**
 * Teleports a player to the given gate and sets the movement direction to facing downwards
 * @param destination_gate The gate to which the player is teleported
 */
void Player::gate_teleport(Stargate *destination_gate) {
	Point teleport_destination = destination_gate->get_entry_point();
	map::MapSections destination_map_section = destination_gate->get_map_section();
	if (map::get_section() != destination_map_section) {
		map::load_section(destination_map_section);
	}

	camera::set_position(teleport_destination);
	set_direction(MovementDirection::DOWN);
	stargate_handler::update_states(teleport_destination);
}

Player::MovementDirection Player::get_direction() {
	return current_direction;
}
