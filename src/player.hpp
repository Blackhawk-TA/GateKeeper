//
// Created by daniel on 21.08.21.
//

#pragma once
#include "utils/utils.hpp"
#include "engine/camera.hpp"
#include "map_objects/stargate.hpp"

using namespace blit;

class Player {
public:
	enum MovementDirection {
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	explicit Player(MovementDirection direction);
	void draw();
	void attack();
	void evade();
	void move(MovementDirection direction);
	static MovementDirection get_direction();
	static void stop_movement();

private:
	const std::map<MovementDirection, Point> movements{
		{UP,    Point(0, -1)},
		{DOWN,  Point(0, 1)},
		{LEFT,  Point(-1, 0)},
		{RIGHT, Point(1, 0)},
	};

	static constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;
	static const std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites;

	const std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> attack_sprites = {
		{UP,    {108, 111, 114, 117}},
		{DOWN,  {0,   3,   6,   9}},
		{LEFT,  {72,  75,  78,  81}},
		{RIGHT, {36,  39,  42,  45}},
	};

	static uint16_t sprite_id;
	static uint8_t sprite_index;
	static std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;
	static bool is_attacking;
	static bool is_evading;
	static bool is_moving;
	static Timer *animation_timer;
	static Timer *action_timer;
	static MovementDirection current_direction;
	static Vec2 evasion_position_modifier;
	static float evasion_modifier;

	const uint8_t ATTACK_TILE_SIZE = 3;
	Surface *characters;
	Surface *player_attack;
	Point position;
	Size spritesheet_size;
	Size attack_spritesheet_size;

	static void animate(Timer &timer);
	static void animate_action(Timer &timer);
	static void entry_teleport(uint8_t building_id, Point next_position);
	void gate_teleport(Stargate *destination_gate);
	void set_direction(MovementDirection direction);
	static bool in_action();
};
