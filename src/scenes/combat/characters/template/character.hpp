//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../../utils/utils.hpp"
#include "../../../../game.hpp"

namespace combat {
	class Character {
	public:
		explicit Character(CharacterData character_data, Point position, Point attack_position);
		virtual ~Character() = default;
		void draw();
		void update(uint32_t time);
		void animate(Timer &timer);

	protected:
		MovementDirection direction;

	private:
		const Size SIZE = Size(1, 1);
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites;
		uint16_t tile_id;
		Point position;
		Point screen_position;
		Point attack_position; //The position at which the attack animation is done
		Size spritesheet_size;

		void walk_to_attack_position();
	};
}