//
// Created by daniel on 21.08.21.
//

#include <assets.hpp>
#include "player.hpp"
#include "../../../engine/effects/transition.hpp"
#include "../../../engine/flags.hpp"
#include "../handlers/stargate_handler.hpp"
#include "../handlers/game_objects.hpp"
#include "../handlers/entry_handler.hpp"

bool Player::attacking = false;
bool Player::evading = false;
Player::MovementDirection Player::current_direction;
Vec2 Player::evasion_position_modifier;
float Player::evasion_modifier = 0;
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
	health = 100;
	dead = false;
	position = get_screen_tiles() / 2;
	spritesheet_size = get_spritesheet_size(player_sprites->bounds);
	attack_spritesheet_size = get_spritesheet_size(player_attack_sprites->bounds);
	elevation_offset = 0;

	//Set player animation tiles
	current_direction = direction;
	animation_sprites = movement_sprites.at(current_direction);
	sprite_id = animation_sprites[0];

	animation_timer.init(animate, 175, -1);
	action_timer.init(animate_action, 75, ANIMATION_SPRITE_COUNT + 1);
}

bool Player::in_action() const {
	return camera::is_moving() || evading || attacking || dead || transition::in_progress();
}

void Player::animate(Timer &timer) {
	if (camera::is_moving() && !transition::in_progress()) {
		//Sprite index increment skips standing sprite because it is already displayed
		sprite_id = animation_sprites[++sprite_index % ANIMATION_SPRITE_COUNT];
	} else {
		sprite_id = animation_sprites[0];
		timer.stop();
	}
}

void Player::animate_action(Timer &timer) {
	if (timer.loop_count <= ANIMATION_SPRITE_COUNT) {
		if (attacking) {
			sprite_id = animation_sprites[sprite_index++ % ANIMATION_SPRITE_COUNT];
		} else if (evading) {
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
			sprite_id = animation_sprites[--sprite_index % ANIMATION_SPRITE_COUNT];
		}
	} else {
		animation_sprites = movement_sprites.at(current_direction);
		sprite_id = animation_sprites[0];
		sprite_index = 0;
		attacking = false;
		evading = false;
		timer.stop();
	}
}

void Player::attack() {
	if (!in_action()) {
		animation_sprites = attack_sprites.at(current_direction);
		sprite_id = animation_sprites[0];
		sprite_index = 0;
		attacking = true;
		action_timer.start();
	}
}

void Player::evade() {
	if (!in_action()) {
		action_timer.start();
		evasion_modifier = 0;
		evasion_position_modifier = Vec2(0, 0);
		sprite_index = ANIMATION_SPRITE_COUNT;
		evading = true;
	}
}

void Player::take_damage(uint8_t damage_amount) {
	if (health - damage_amount > 0) {
		health -= damage_amount;
	} else {
		dead = true;
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
		transition::start([destination_gate] {
			gate_teleport(destination_gate);
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
			if (entry_handler::enter(next_position)) {
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
	if (attacking) {
		screen.blit(
			player_attack_sprites,
			Rect((sprite_id % attack_spritesheet_size.w) * TILE_SIZE, (sprite_id / attack_spritesheet_size.h) * TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE, TILE_SIZE * ATTACK_TILE_SIZE),
			world_to_screen(position - Point(1,1)) - Point(0, elevation_offset),
			SpriteTransform::NONE
		);
	} else {
		screen.blit(
			player_sprites,
			Rect((sprite_id % spritesheet_size.w) * TILE_SIZE, (sprite_id / spritesheet_size.h) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
			world_to_screen(position) + world_to_screen(evasion_position_modifier) - Point(0, elevation_offset),
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
	change_direction(MovementDirection::DOWN, false);
	game_objects::update_states(teleport_destination);
}

Player::MovementDirection Player::get_direction() {
	return current_direction;
}

void Player::stop_animation() {
	animation_timer.stop();
	sprite_id = animation_sprites[0];
}

bool Player::is_dead() const {
	return dead;
}

uint8_t Player::get_health() const {
	return health;
}
