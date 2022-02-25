//
// Created by daniel on 25.02.22.
//

#pragma once
#include "../../../../../utils/types.hpp"
#include "../../characters/enemy.hpp"

namespace game::enemy_handler {
	void init();
	void cleanup();

	/**
	 * Respawns all enemies by setting their 'is_active' value to true, if they can be respawned.
	 * The check if an enemy can be respawned is done within the enemy class itself
	 */
	void respawn();
}
