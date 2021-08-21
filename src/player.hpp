//
// Created by daniel on 21.08.21.
//

#pragma once
#include "utils/utils.hpp"

using namespace blit;

class Player {
public:
	explicit Player();
	void draw();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	Point update_camera();

private:
	const uint8_t velocity = 5;
	const uint16_t tile_id = 5;

	Point start_position;
	Point position;
	Point camera;
	Point camera_offset;
	Point sprite_sheet_size;
	bool is_moving = false;

	void move(Point movement);
};
