//
// Created by daniel on 25.02.22.
//

#pragma once
#include "../../../../../utils/types.hpp"
#include "../../characters/enemy.hpp"

namespace game::enemy_handler {
	void init();
	void cleanup();
	void delete_enemy(Signature &signature);

	/**
	 * Respawns all enemies by setting their 'is_active' value to true, if they can be respawned.
	 * If they cannot be respawned they are deleted from the game objects collection.
	 */
	void respawn();

	/**
	 * Gets the pointer to a single enemy by its signature if it exists
	 * @param signature The signature of the enemy
	 * @return The pointer to the enemy object or nullptr if it does not exist
	 */
	Enemy* get_enemy(Signature &signature);
}
