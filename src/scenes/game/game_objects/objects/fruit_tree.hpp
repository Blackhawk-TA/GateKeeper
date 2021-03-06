//
// Created by daniel on 06.11.21.
//

#pragma once
#include "../template/game_object.hpp"

namespace game {
	class FruitTree : public GameObject {
	private:
		const uint16_t TILE_ID_TREE = 1349;
		const uint16_t TILE_ID_FRUITS = 1541;
		const Size FRUIT_SIZE = Size(3, 1);
		const Point FRUIT_OFFSET = Point(0, 1);
		const uint16_t GROW_TIME_MS = 60000;

	public:
		explicit FruitTree(map::MapSection map_section, Point position, bool player_usable);
		~FruitTree() override = default;
		void draw() override;
		void update(uint32_t time) override;
		bool player_interact() override;
		ObjectType get_type() override;
	};
}