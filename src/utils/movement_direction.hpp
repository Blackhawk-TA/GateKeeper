//
// Created by daniel on 30.12.21.
//

#pragma once
#include "utils.hpp"

enum MovementDirection {
	NO_DIRECTION = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

/**
 * Calculates the movement direction from from two points, so that the character is facing forwards when moving between those.
 * @param p1 The start position
 * @param p2 The target position
 * @return The calculated movement direction
 */
MovementDirection calculate_direction_from_points(Point p1, Point p2);

/**
 * Inverts the movement direction
 * @param direction The current movement direction
 * @return The inverted movement direction
 */
MovementDirection invert_direction(MovementDirection direction);
