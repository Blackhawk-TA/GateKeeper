//
// Created by daniel on 19.12.21.
//

#pragma once
#include "../../../game_objects/objects/dungeon_door.hpp"

namespace dungeon_door_handler {
	void init();

	/**
	 * Opens the door with the corresponding signature
	 * @param signature The signature of the door
	 * @return True if the door was found and could be opened, else false
	 */
	bool open_door(GameObject::Signature signature);
}
