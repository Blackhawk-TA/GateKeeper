//
// Created by D069765 on 18.10.2021.
//

#pragma once
#include <iostream>
#include "../utils/utils.hpp"

class IScene {
public:
	virtual ~IScene() = default;

	/**
	 * This function is called to perform rendering of the game.
	 * @param time the amount of milliseconds elapsed since the start of your game
	 */
	virtual void render(uint32_t time) = 0;

	/**
	 * This is called to update your game state.
	 * @param time amount of milliseconds elapsed since the start of your game
	 */
	virtual void update(uint32_t time) = 0;

	/**
	 * This is called to handle all user inputs, e.g. button presses.
	 */
	virtual void inputs() = 0;
};
