//
// Created by daniel on 21.08.21.
//

#pragma once
#include "utils/utils.hpp"
#include "camera.hpp"

using namespace blit;

class Player {
public:
	explicit Player(Camera *game_camera);
	void draw();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	static void stop_movement();

private:
	enum MovementDirection {
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	static constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;
	static uint16_t sprite_index;
	static std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;
	static bool is_moving;
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_down_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_left_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_right_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_up_sprites{};
	MovementDirection current_direction;

	static Camera *camera;
	static Timer *animation_timer;
	Surface *characters;
	Point start_position;
	Point position;
	Point sprite_sheet_size;

	static void animate(Timer &timer);
	void move(Point movement, MovementDirection direction);
};
