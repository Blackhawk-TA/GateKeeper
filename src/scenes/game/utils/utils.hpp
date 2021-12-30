//
// Created by daniel on 28.12.21.
//

#include "../../../utils/utils.hpp"
#include "../../../engine/map.hpp"
#include "../player.hpp"

namespace game::utils {
	/**
	 * Teleports the player to a new map section, saves the game and loads the required game objects
	 * @param map_section The map section to load
	 */
	void teleport_player(map::MapSection map_section, Point position, Player::MovementDirection direction, uint8_t save_id);
}
