//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../objects/sign.hpp"
#include "../../objects/fruit_tree.hpp"
#include "../../objects/carrot_bed.hpp"
#include "../../characters/villager.hpp"
#include "../../characters/enemy.hpp"
#include "../../characters/story_character.hpp"
#include "../../characters/gear_villager.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_grassland_objects(uint8_t save_id, StoryState story_state) {
		std::vector<GameObject*> objects = {
			//TODO disable endgame gate
			new Stargate(map::GRASSLAND, Point(21, 7), GRASSLAND_ENDGAME, DESERT, false),
			new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false),
			new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false),
			new Stargate(map::DESERT, Point(4, 57), DESERT, GRASSLAND_ENDGAME, false),

			new Sign(map::GRASSLAND, Point(24, 44), Sign::WOOD, "Trees grow fruits which can be eaten. They regrow after harvesting. Carrots can be planted and harvested."),
			new Sign(map::GRASSLAND, Point(25, 12), Sign::WOOD, "The Stargate is a portal to other worlds! It was closed to keep the village safe."),
			new Sign(map::GRASSLAND, Point(24, 19), Sign::WOOD, "Your house"),
			new Sign(map::GRASSLAND, Point(18, 12), Sign::WOOD, "The Hospital"),
			new FruitTree(map::GRASSLAND, Point(11, 16), true),
			new FruitTree(map::GRASSLAND, Point(21, 42), true),
			new CarrotBed(map::GRASSLAND, Point(16, 42)),
			new CarrotBed(map::GRASSLAND, Point(17, 42)),
			new CarrotBed(map::GRASSLAND, Point(18, 42)),
			new CarrotBed(map::GRASSLAND, Point(16, 43)),
			new CarrotBed(map::GRASSLAND, Point(17, 43)),
			new CarrotBed(map::GRASSLAND, Point(18, 43)),
			new Villager(map::GRASSLAND, Point(24, 15), 0, LEFT, "Hello there!"),
			new Enemy(map::GRASSLAND, Point(21, 10), BLUE_GUARD, RIGHT, save_id, false, "LET'S FIGHT!", false),
			new Enemy(map::GRASSLAND, Point(23, 10), BLUE_GUARD, LEFT, save_id, false, "LET'S FIGHT!", false),

			//TODO remove
			new GearVillager(map::GRASSLAND, Point(23, 17), 4, LEFT, "Here take that dagger.", "You already have a dagger, go use it.", GEAR_DAGGER),


		};

		if (story_state == StoryState::INITIAL_GEAR) {
			std::string msg = "Hello traveler I'm the elder of this village. The gate behind you is a portal to different worlds. "
							  "Unfortunately the new king limits gate travel by guarding the gate to the castle from which "
							  "he suppresses us. I hope someday a traveler arrives that brings the kings reign of terror to an end. "
							  "You look well armed, do you think you could try your best to liberate us from that brutal king?";
			std::string alt_msg = "We can only be free once the brutal king is dead. He lives in a castle in middle of a desert.";
 			objects.emplace_back(new StoryCharacter(map::GRASSLAND, Point(28, 13), 12, LEFT, true, msg, alt_msg));

			objects.emplace_back(new Villager(map::GRASSLAND, Point(39, 17), 4, DOWN, "I cannot let you pass yet. You should talk to the elder first."));
			objects.emplace_back(new Villager(map::GRASSLAND, Point(52, 51), 268, DOWN, "I cannot let you pass yet. You should talk to the elder first."));
		}

		return objects;
	}
}
