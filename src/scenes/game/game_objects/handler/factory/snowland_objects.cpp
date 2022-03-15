//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/stargate.hpp"
#include "../../characters/enemy.hpp"
#include "../../objects/sign.hpp"
#include "../../characters/gear_villager.hpp"
#include "../../objects/chest.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_snowland_objects(uint8_t save_id, StoryState story_state) {
		return {
			new Stargate(map::GRASSLAND, Point(51, 10), GRASSLAND, WINTER, false),
			new Stargate(map::SNOWLAND, Point(8, 37), WINTER, GRASSLAND, false),

			new Sign(map::SNOWLAND, Point(11, 13), Sign::WOOD, "The Hospital"),
			new Sign(map::SNOWLAND, Point(21, 20), Sign::WOOD, "The Weapon Shop"),
			new Enemy(map::SNOWLAND, Point(18, 46), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(42, 29), ICE_BEAR, LEFT, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(57, 33), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(42, 5), ICE_BEAR, UP, save_id, true, "GRR!"),
			new Enemy(map::SNOWLAND, Point(54, 19), ICE_BEAR, UP, save_id, true, "GRR!"),

			new GearVillager(map::SNOWLAND, Point(50, 52), 4, DOWN, "What you don't have a sword? It's far too dangerous out here without any weapons. Here take mine!", "The sword will help you to protect yourself against wild animals like bears.", GEAR_SWORD),

			new Chest(map::SNOWLAND, Point(16, 38)),
			new Chest(map::SNOWLAND, Point(22, 35)),
			new Chest(map::SNOWLAND, Point(32, 18)),
			new Chest(map::SNOWLAND, Point(53, 52)),
			new Chest(map::SNOWLAND, Point(54, 52)),
			new Chest(map::SNOWLAND, Point(60, 19)),
		};
	}
}
