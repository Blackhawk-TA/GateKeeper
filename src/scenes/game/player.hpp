//
// Created by daniel on 21.08.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "../../engine/camera.hpp"
#include "game_objects/objects/stargate.hpp"

using namespace blit;

//TODO rewrite so it is similar to character
class Player {
public:
	enum MovementDirection { //TODO player and character can use the same MovementDirection
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	explicit Player(MovementDirection direction, uint8_t player_health);
	void draw();
	void attack();
	void evade();
	void move(MovementDirection direction);
	static bool is_dead();
	static uint8_t get_health();
	static void take_damage(uint8_t damage_amount);
	static void heal(uint8_t heal_amount);
	static MovementDirection get_direction();
	static void change_direction(MovementDirection direction, bool animate = true);
	static void start_cut_scene();
	static bool in_cut_scene();

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
	static bool attacking;
	static bool evading;
	static bool cut_scene;
	static MovementDirection current_direction;
	static Vec2 evasion_position_modifier;
	static float evasion_modifier;
	static uint8_t health;
	static bool dead;

	const uint8_t ATTACK_TILE_SIZE = 3;
	Timer animation_timer;
	Timer action_timer;
	Point position;
	Size spritesheet_size;
	Size attack_spritesheet_size;
	uint8_t elevation_offset;

	static void animate(Timer &timer);
	static void animate_action(Timer &timer);
	static void gate_teleport(Stargate *destination_gate);
	static bool in_action();
	void stop_animation();
};
