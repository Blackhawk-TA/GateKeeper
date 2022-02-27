//
// Created by daniel on 19.12.21.
//

#pragma once
#include "../template/game_object.hpp"

namespace game {
	class DungeonDoor : public GameObject {
	public:
		explicit DungeonDoor(map::MapSection map_section, Point position);
		~DungeonDoor() override = default;
		bool player_interact() override;
		ObjectType get_type() override;
		bool open();

	private:
		const uint16_t TILE_ID_OPEN = 686;
		const uint16_t TILE_ID_CLOSED = 558;

		enum State {
			OPEN = 1,
			CLOSED = 2,
		};

		State state;

		void set_state(uint8_t new_state) override;
		bool check_collision(Point next_position) override;
	};
}
