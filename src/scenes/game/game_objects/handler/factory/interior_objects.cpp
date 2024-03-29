//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../characters/salesman.hpp"
#include "../../characters/nurse.hpp"
#include "../../characters/story_character.hpp"
#include "../../objects/chest.hpp"
#include "../../characters/villager.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_interior_objects(uint8_t save_id, StoryState story_state) {
		std::vector<GameObject*> objects = {
			new Salesman(map::INTERIOR, Point(31, 20), Salesman::Supply::ITEMS),
			new Salesman(map::INTERIOR, Point(25, 55), Salesman::Supply::GEAR),
			new Nurse(map::INTERIOR, Point(54, 20)),
			new Nurse(map::INTERIOR, Point(54, 37)),
			new Villager(map::INTERIOR, Point(25, 39), 268, UP, "Hello! I really like watching TV."),
			new Villager(map::INTERIOR, Point(6, 56), 264, RIGHT, "Oh hey there! It is cold outside, you can stay here and warm up if you want to."),
			new Villager(map::INTERIOR, Point(27, 6), 136, LEFT, "Hey, you just moved to our village right? Welcome!"),

			new Chest(map::INTERIOR, Point(11, 3)),
			new Chest(map::INTERIOR, Point(45, 3)),
			new Chest(map::INTERIOR, Point(4, 54)),
			new Chest(map::INTERIOR, Point(11, 21)),
			new Chest(map::INTERIOR, Point(11, 41)),
		};

		if (story_state >= StoryState::FIRST_DEATH && story_state != StoryState::COMPLETED) {
			std::string msg = "Oh hey, you're awake! I'm not sure if you can remember what happened. You challenged the "
							  "guards at the gate. They struck you down and stole all your weapons. Then they went back "
							  "through the gate while you were unconscious and destroyed it to prevent us from ever "
							  "coming back. Now we have no possibility to reach the castle where the king suppresses our villagers from.";
			std::string alt_msg = "You need new weapons. In the north-east there should be a gate, try your luck there.";
			objects.emplace_back(new StoryCharacter(map::INTERIOR, Point(51, 21), 12, LEFT, false, msg, alt_msg));
		} else if (story_state == StoryState::COMPLETED) {
			objects.emplace_back(new StoryCharacter(map::INTERIOR, Point(49, 6), 12, LEFT, false, "You defeated the king! Thank you in the name of every villager! So what are your plans now? Did you already collect all four crystals?", "Thanks again!"));
		}

		return objects;
	}
}
