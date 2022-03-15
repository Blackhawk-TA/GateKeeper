//
// Created by daniel on 15.03.22.
//

#pragma once

#include "../template/game_object.hpp"

namespace game {
	class Chest : public GameObject {
	public:
		explicit Chest(map::MapSection map_section, Point position);
		~Chest() override = default;
		void load_save(Data data) override;
		bool player_interact() override;
		ObjectType get_type() override;
		void set_state(uint8_t new_state) override;

	private:
		enum State {
			OPEN = 1,
			CLOSED = 2,
		};
		State state;
		uint16_t CLOSED_TILE_ID = 1206;
		uint16_t OPENED_TILE_ID = 1074;
	};
}
