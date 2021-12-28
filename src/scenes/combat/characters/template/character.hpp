//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../../utils/utils.hpp"

namespace combat {
	class Character {
	public:
		explicit Character(Point position);
		virtual ~Character() = default;
		void draw();

	private:
		const Size SIZE = Size(1, 1);
		Point position;
		Point screen_position;
		Size spritesheet_size;
		uint16_t tile_id;
	};
}