//
// Created by daniel on 21.08.21.
//

#pragma once
#include "utils/utils.hpp"
#include "engine/camera.hpp"

using namespace blit;

class Player {
public:
	enum MovementDirection {
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	explicit Player(Camera *game_camera);
	void draw();
	void move(MovementDirection direction);
	static void stop_movement();

private:
	const std::map<MovementDirection, Point> movements {
			{UP, Point(0, -1)},
			{DOWN, Point(0, 1)},
			{LEFT, Point(-1, 0)},
			{RIGHT, Point(1, 0)},
	};

	static constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;
	const std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites = {
			{UP, {48, 49, 50, 51}},
			{DOWN, {0, 1, 2, 3}},
			{LEFT, {16, 17, 18, 19}},
			{RIGHT, {32, 33, 34, 35}}
	};

	static uint16_t sprite_index;
	static std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;
	static bool is_moving;
	static Camera *camera;
	static Timer *animation_timer;

	Surface *characters;
	Point start_position;
	Point position;
	Point sprite_sheet_size;
	MovementDirection current_direction;

	static void animate(Timer &timer);
	static void teleport(uint8_t building_id, Point next_position);
};
