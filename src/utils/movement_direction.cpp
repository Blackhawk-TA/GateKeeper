//
// Created by daniel on 30.12.21.
//

#include "movement_direction.hpp"

MovementDirection calculate_direction_from_points(Point p1, Point p2) {
	if (p1.x != p2.x && p1.y != p2.y) {
		return NO_DIRECTION;
	}

	if (p1.x < p2.x) {
		return RIGHT;
	} else if (p1.x > p2.x) {
		return LEFT;
	} else if (p1.y < p2.y) {
		return DOWN;
	} else if (p1.y > p2.y) {
		return UP;
	} else {
		return NO_DIRECTION;
	}
}

MovementDirection invert_direction(MovementDirection direction) {
	switch (direction) {
		case UP:
			return DOWN;
		case DOWN:
			return UP;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		default:
			return NO_DIRECTION;
	}
}
