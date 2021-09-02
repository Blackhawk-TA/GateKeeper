//
// Created by daniel on 22.08.21.
//

#pragma once
#include "utils/utils.hpp"

using namespace blit;

class Camera {
public:
	explicit Camera();
	bool is_moving() const;
	Point get_world_position() const;
	Point get_screen_position() const;
	void set_position(Point &position);
	void move(Point &offset);
	void update_position();

private:
	const uint8_t camera_scale = 100;
	const float camera_scale_float = 100.0f;

	bool moving;
	uint8_t velocity;
	Point camera_position;
	Point camera_offset;
};
