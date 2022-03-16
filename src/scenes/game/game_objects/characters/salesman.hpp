//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Salesman : public Character {
	public:
		enum Supply {
			ITEMS = 1,
			GEAR = 2,
		};

		explicit Salesman(map::MapSection map_section, Point position, Supply supply);
		~Salesman() override = default;

	private:
		const uint8_t BAR_HEIGHT = 1;
		Supply supply;
		std::string message;

		bool player_interact() override;
		void close_textbox() override;
	};
}
