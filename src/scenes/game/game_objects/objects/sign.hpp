//
// Created by daniel on 06.11.21.
//

#pragma once

#include "../template/game_object.hpp"

namespace game {
	class Sign : public GameObject {
	public:
		enum SpriteType {
			STONE = 1,
			WOOD = 2,
		};

		explicit Sign(map::MapSection map_section, Point position, Sign::SpriteType sprite_type, std::string text);
		~Sign() override = default;
		bool player_interact() override;
		ObjectType get_type() override;

	private:
		std::string text;

		void set_sprite(SpriteType sprite_type);
	};
}
