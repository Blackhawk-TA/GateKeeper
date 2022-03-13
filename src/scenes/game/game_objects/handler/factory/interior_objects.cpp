//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../characters/salesman.hpp"
#include "../../characters/nurse.hpp"
#include "../../characters/story_character.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_interior_objects(uint8_t save_id, StoryState story_state) {
		std::vector<GameObject*> objects = {
			new Salesman(map::INTERIOR, Point(31, 20)),
			new Nurse(map::INTERIOR, Point(54, 20)),
			new Nurse(map::INTERIOR, Point(54, 37)),
		};

		if (story_state == StoryState::REMOVE_GEAR || story_state == StoryState::FOUND_GEAR) {
			std::string msg = "Oh hey, you're awake! I'm not sure if you can remember what happened. You challenged the "
							  "guards at the gate. They struck you down and stole all your weapons. They went back back "
							  "through the gate while you were unconscious and destroyed it to prevent us from ever "
							  "coming back. Now we no possibility to reach the castle were the new king suppresses our villagers from.";
			std::string alt_msg = "You need new weapons. In the north-east there should be a gate, try your luck there.";
			objects.emplace_back(new StoryCharacter(map::INTERIOR, Point(51, 21), 12, LEFT, false, msg, alt_msg));
		}

		return objects;
	}
}
