//
// Created by daniel on 27.02.22.
//

#pragma once
#include "../template/game_object.hpp"

namespace game::game_objects {
	/**
	 * Loads saved objects into each game object
	 * @param saved_objects The saved game objects pointer array
	 * @param story_state The current state of the story, depending on which game objects can be spawned
	 */
	void load_saves(std::array<GameObject::Save, MAX_GAME_OBJECTS> &saved_objects, StoryState story_state);

	/**
	 * Gets array with save structs of all game objects objects on the current map section.
	 * Only the game objects of the current map section are stored in memory and therefore only those can be returned.
	 * @return The game object saves of the current map section
	 */
	std::array<GameObject::Save, MAX_GAME_OBJECTS> get_section_saves();

	/**
	 * Gets all game object saves by merging the old ones from different map sections with the ones im memory from the current map section.
	 * This is necessary because there are never all game objects in memory.
	 * @param save_id The id of the current save to get the saved game objects from other map sections
	 * @return A full list of game object saves
	 */
	//TODO causes invalid write/read on save. It works for items, why not for game objects?
	std::array<GameObject::Save, MAX_GAME_OBJECTS> get_global_saves(uint8_t save_id);
}
