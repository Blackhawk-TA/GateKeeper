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

namespace game::game_objects {
	std::vector<GameObject*> create_grassland_objects(uint8_t save_id) {
		return {
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
			new Villager(map::GRASSLAND, Point(13, 14), 12, RIGHT, "Hello I'm the elder of this village."),
//			new Villager(map::GRASSLAND, Point(39, 17), 4, RIGHT, "There is a Gate in this forest, but I can't let you pass without permission of the elder. It could be too dangerous for you."),
			new Enemy(map::GRASSLAND, Point(22, 14), BLUE_GUARD, DOWN, save_id, false, "LET'S FIGHT!"),
		};
	}
}
