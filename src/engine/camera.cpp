//
// Created by daniel on 22.08.21.
//

#include "camera.hpp"

const uint8_t camera_scale = 100;
const float camera_scale_float = 100.0f;

bool moving;
uint8_t velocity;
Point camera_position;
Point camera_offset;

void camera::init(Point start_position) {
	moving = false;
	velocity = 5;
	camera_position = (start_position - get_screen_tiles() / 2) * camera_scale;
	camera_offset = Point(0, 0);
}

bool camera::is_moving() {
	return moving;
}

Point camera::get_world_position() {
	return camera_position / camera_scale;
}

Point camera::get_screen_position() {
	return world_to_screen((float) camera_position.x / camera_scale_float,
	                       (float) camera_position.y / camera_scale_float);
}

void camera::set_position(Point position) {
	camera_position = (position - get_screen_tiles() / 2) * camera_scale;
}

void camera::move(Point &offset) {
	camera_offset = offset * camera_scale;
	moving = true;
}

void camera::update_position() {
	if (camera_offset.x != 0) {
		if (camera_position.x < camera_position.x + camera_offset.x) {
			camera_position.x += velocity;
			camera_offset.x -= velocity;
		} else if (camera_position.x > camera_position.x + camera_offset.x) {
			camera_position.x -= velocity;
			camera_offset.x += velocity;
		}
	} else if (camera_offset.y != 0) {
		if (camera_position.y < camera_position.y + camera_offset.y) {
			camera_position.y += velocity;
			camera_offset.y -= velocity;
		} else if (camera_position.y > camera_position.y + camera_offset.y) {
			camera_position.y -= velocity;
			camera_offset.y += velocity;
		}
	} else {
		moving = false;
	}
}
