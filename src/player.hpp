//
// Created by daniel on 21.08.21.
//

#pragma once
#include "utils/utils.hpp"
#include "utils/camera.hpp"

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
	const uint16_t tile_id = 5;

	Camera *camera;
	Point start_position;
	Point position;
	Point sprite_sheet_size;

	void move(Point movement);
};
