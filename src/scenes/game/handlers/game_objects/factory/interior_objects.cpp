//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../../game_objects/characters/salesman.hpp"
#include "../../../game_objects/characters/nurse.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_interior_objects(uint8_t save_id) {
		return {
			new Salesman(map::INTERIOR, Point(31, 20)),
			new Nurse(map::INTERIOR, Point(54, 20)),
		};
	}
}
