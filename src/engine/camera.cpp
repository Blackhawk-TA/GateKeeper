//
// Created by daniel on 22.08.21.
//

#include "camera.hpp"

//TODO class not required, use namespace with namespace variables
Camera::Camera() {
	moving = false;
	velocity = 5;
	camera_position = Point(0, 0);
	camera_offset = Point(0, 0);
}

bool Camera::is_moving() const {
	return moving;
}

Point Camera::get_world_position() const {
	return camera_position / camera_scale;
}

Point Camera::get_screen_position() const {
	return world_to_screen((float) camera_position.x / camera_scale_float, (float) camera_position.y / camera_scale_float);
}

void Camera::set_position(Point &position) {
	camera_position = position * camera_scale;
}

void Camera::move(Point &offset) {
	camera_offset = offset * camera_scale;
	moving = true;
}

void Camera::update_position() {
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
