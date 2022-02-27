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

		bool player_interact() override;
		void close_textbox() override;
	};
}
