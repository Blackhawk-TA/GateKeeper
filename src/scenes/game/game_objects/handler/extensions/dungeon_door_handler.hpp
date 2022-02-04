//
// Created by daniel on 19.12.21.
//

#pragma once
#include "../../objects/dungeon_door.hpp"

namespace game::dungeon_door_handler {
	void init();
	void delete_door(Signature &signature);
	void cleanup();

	/**
	 * Opens the door with the corresponding signature
	 * @param signature The signature of the door
	 * @return True if the door was found and could be opened, else false
	 */
	bool open_door(Signature signature);
}
