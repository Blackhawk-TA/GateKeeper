//
// Created by daniel on 20.02.22.
//

#pragma once
#include "../template/game_object.hpp"

namespace game {
	class Crystal : public GameObject {
	public:
		enum CrystalType {
			PURPLE = 1,
			YELLOW = 2,
			BLUE = 3,
			RED = 4,
		};

		explicit Crystal(map::MapSection map_section, Point position, CrystalType type);
		~Crystal() override = default;
		void draw() override;
		bool player_interact() override;
		void update_state(Point next_position) override;
		ObjectType get_type() override;
		void update(uint32_t time) override;

	private:
		CrystalType type;
		uint16_t tile_id_crystal;

		void set_state(uint8_t new_state) override;
	};
}
