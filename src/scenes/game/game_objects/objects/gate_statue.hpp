//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "../template/game_object.hpp"
#include "../../../../engine/map.hpp"
#include "../../../../engine/ui/textbox.hpp"

namespace game {
	class GateStatue : public GameObject {
	private:
		enum RenderStates {
			DEPLETED = 1,
			INACTIVE = 2,
			ACTIVE = 3
		};

		const uint16_t TILE_ID_EMPTY = 2046;
		const uint16_t TILE_ID_INACTIVE = 364;
		const uint16_t TILE_ID_ACTIVE = 2047;

		RenderStates state;

		void set_state(uint8_t new_state) override;
		void set_player_usable(bool usable) override;

	public:
		explicit GateStatue(map::MapSection map_section, Point position);
		~GateStatue() override = default;
		bool player_interact() override;
		void update_state(Point next_position) override;
		ObjectType get_type() override;
	};
}
