//
// Created by daniel on 23.01.22.
//

#include "object_factory.hpp"
#include "../../objects/gate_statue.hpp"
#include "../../objects/sign.hpp"
#include "../../characters/enemy.hpp"
#include "../../objects/dungeon_door.hpp"
#include "../../objects/lever.hpp"
#include "../../objects/crystal.hpp"
#include "../../objects/chest.hpp"

namespace game::game_objects {
	std::vector<GameObject*> create_dungeon_objects(uint8_t save_id, StoryState story_state) {
		//Settings for dungeon
		uint8_t enabled_lever = blit::random() % 3;

		//The signature of the door that the levers open
		Signature interaction_signature = {
			map::DUNGEON,
			14,
			36
		};

		return {
			//Main dungeon
			new GateStatue(map::DUNGEON, Point(14, 22)),
			new Sign(map::DUNGEON, Point(15, 23), Sign::STONE, "This dungeon was created to hide a gate part to repair the gate in case it gets destroyed."),
			new DungeonDoor( static_cast<map::MapSection>(interaction_signature.map_section), Point(interaction_signature.x, interaction_signature.y)),

			new Enemy(map::DUNGEON, Point(36, 36), 1, SPIDER, DOWN, save_id),
			new Enemy(map::DUNGEON, Point(42, 36), 1, SPIDER, DOWN, save_id),
			new Enemy(map::DUNGEON, Point(48, 36), 1, SPIDER, DOWN, save_id),
			new Enemy(map::DUNGEON, Point(11, 35), 1, SPIDER, RIGHT, save_id),
			new Enemy(map::DUNGEON, Point(18, 35), 1, SPIDER, LEFT, save_id),

			new Lever(map::DUNGEON, Point(37, 36), interaction_signature, enabled_lever == 0),
			new Lever(map::DUNGEON, Point(43, 36), interaction_signature, enabled_lever == 1),
			new Lever(map::DUNGEON, Point(49, 36), interaction_signature, enabled_lever == 2),

			new Chest(map::DUNGEON, Point(11, 24)),
			new Chest(map::DUNGEON, Point(18, 24)),

			//Mini dungeon
			new Crystal(map::DUNGEON, Point(58, 2), Crystal::PURPLE),

			new Chest(map::DUNGEON, Point(55, 3)),
			new Chest(map::DUNGEON, Point(61, 3)),

			new Enemy(map::DUNGEON, Point(56, 15), 5, SPIDER, RIGHT, save_id),
			new Enemy(map::DUNGEON, Point(60, 15), 5, SPIDER, LEFT, save_id),
			new Enemy(map::DUNGEON, Point(56, 10), 5, SPIDER, RIGHT, save_id),
			new Enemy(map::DUNGEON, Point(60, 10), 5, SPIDER, LEFT, save_id),
		};
	}
}
