//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../../utils/utils.hpp"
#include "../../../../game.hpp"

namespace combat {
	class Character {
	public:
		explicit Character(CharacterData character_data, Point position);
		virtual ~Character() = default;
		void draw();

	private:
		const Size SIZE = Size(1, 1);
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites;
		uint16_t tile_id;
		Point position;
		Point screen_position;
		Size spritesheet_size;
	};
}