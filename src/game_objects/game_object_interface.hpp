//
// Created by daniel on 25.10.21.
//

#pragma once
#include "../utils/utils.hpp"

template<typename RenderState>

class IGameObject {
public:
	/**
	 * Check if the game object collides with the player's next position
	 * @param next_position The next position of the player
	 * @return True, if a collision takes place, else false
	 */
	virtual bool check_collision(Point next_position) = 0;

	/**
	 * Draw the game object
	 */
	virtual void draw() = 0;

	/**
	 * Called when the player interacts with a game object
	 * @return True, if interaction successful, else false
	 */
	virtual bool interact() = 0;

protected:
	/**
	 * Changes the render state of a game object
	 * @param new_state The new render state
	 */
	virtual void set_state(RenderState new_state) = 0;
};
