//
// Created by daniel on 26.02.22.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class GearVillager : public Character {
	private:
		std::string message;
		std::string alt_message;
		GEAR_TYPE gear_type;

		void set_state(uint8_t new_state) override;

	public:
		explicit GearVillager(
			map::MapSection map_section,
			Point position,
			uint16_t tile_id,
			MovementDirection direction,
			std::string message,
			std::string alt_message,
			GEAR_TYPE gear_type
		);
		~GearVillager() override = default;

		void update_state(Point next_position) override;
		bool player_interact() override;
		void close_textbox() override;
	};
}
