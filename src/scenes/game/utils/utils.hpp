//
// Created by daniel on 28.12.21.
//

#include "../../../utils/utils.hpp"
#include "../../../engine/map.hpp"
#include "../game_objects/player.hpp"

namespace game::utils {
	/**
	 * Teleports the player to a new map section, saves the game and loads the required game objects
	 * @param map_section The map section to load
	 */
	void teleport_player(map::MapSection map_section, Point position, MovementDirection direction, uint8_t save_id, StoryState story_state);

	/**
	 * Gets the attack sprites by the first tile id of a character
	 * @param tile_id The first tile id of a character
	 */
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> get_attack_sprites(CombatCharacterType type);
}
