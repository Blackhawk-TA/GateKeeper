//
// Created by daniel on 19.12.21.
//

#include "dungeon_door_handler.hpp"
#include "../game_object_handler.hpp"

namespace game {
	std::vector<DungeonDoor*> doors;

	void dungeon_door_handler::init() {
		std::vector<GameObject *> game_object_collection = game_objects::get_collection();

		for (GameObject *game_object: game_object_collection) {
			if (game_object->get_type() == GameObject::DungeonDoorType) {
				doors.push_back((DungeonDoor *) game_object);
			}
		}
	}

	void dungeon_door_handler::cleanup() {
		doors.clear();
	}

	bool dungeon_door_handler::open_door(GameObject::Signature signature) {
		bool is_open = false;
		uint16_t i = 0;

		while (!is_open && i < doors.size()) {
			if (game_objects::has_equal_signature(signature, doors.at(i)->get_signature())) {
				is_open = doors.at(i)->open();
				i++;
			}
		}

		return is_open;
	}
}