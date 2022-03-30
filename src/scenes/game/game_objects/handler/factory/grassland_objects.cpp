//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../objects/sign.hpp"
#include "../../objects/fruit_tree.hpp"
#include "../../objects/carrot_bed.hpp"
#include "../../characters/villager.hpp"
#include "../../characters/story_character.hpp"
#include "../../objects/chest.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_grassland_objects(uint8_t save_id, StoryState story_state) {
		std::vector<GameObject*> objects = {
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
			new Villager(map::GRASSLAND, Point(20, 15), 260, RIGHT, "A myth says that there are crystals hidden in multiple dungeons. It is said that they grant special powers to their owner."),

			new Chest(map::GRASSLAND, Point(11, 14)),
			new Chest(map::GRASSLAND, Point(35, 38)),
			new Chest(map::GRASSLAND, Point(50, 13)),
		};

		if (story_state == StoryState::START) {
			std::string msg = "Hello! It's great that you decided to move to our village. Let me give you a short introduction. "
							  "I'm the elder of this village. To the north there is a gate that is a portal to different worlds. "
							  "This gate leads to the castle of the king but it is heavily guarded because the king is suppressing us. "
							  "He is afraid of losing his power, but nobody was brave enough to challenge him yet. "
							  "I hope some day a great warrior arrives that brings the kings reign of terror to an end. "
							  "You look well armed, maybe you could be this warrior? I really hope so. However, have a nice day!";
			std::string alt_msg = "We can only be free once the brutal king is dead. He lives in a castle in middle of a desert.";
 			objects.emplace_back(new StoryCharacter(map::GRASSLAND, Point(27, 22), 12, UP, true, msg, alt_msg));
			objects.emplace_back(new Villager(map::GRASSLAND, Point(39, 17), 4, DOWN, "I cannot let you pass yet. You should talk to the elder in the village first."));
			objects.emplace_back(new Villager(map::GRASSLAND, Point(52, 51), 268, DOWN, "I cannot let you pass yet. You should talk to the elder in the village first."));
		}

		return objects;
	}
}
