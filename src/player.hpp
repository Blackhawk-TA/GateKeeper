//
// Created by daniel on 21.08.21.
//

#pragma once
#include "utils/utils.hpp"
#include "camera.hpp"

using namespace blit;

class Player {
public:
	explicit Player(Camera *camera);
	void draw();
	void move_up();
	void move_down();
	void move_left();
	void move_right();

private:
	static constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;
	static uint16_t sprite_index;
	static std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_down_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_left_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_right_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> move_up_sprites{};

	Camera *camera;
	Surface *characters;
	Point start_position;
	Point position;
	Point sprite_sheet_size;
	Timer animation_timer;

	void move(Point movement);
	static void animate(Timer &timer);
};
