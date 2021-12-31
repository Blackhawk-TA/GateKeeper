//
// Created by daniel on 26.12.21.
//

#pragma once
#include "../../../../utils/utils.hpp"
#include "../../../../game.hpp"
#include "../../../../utils/movement_direction.hpp"

namespace combat {
	class Character {
	public:
		explicit Character(CharacterData character_data, Point position, Point attack_position);
		virtual ~Character() = default;
		void draw();
		void update(uint32_t time);
		void animate(Timer &timer);
		void set_attacking(bool value);
		uint8_t get_health() const;
		static const uint8_t MAX_HEALTH = 100;

	protected:
		MovementDirection direction;
		uint8_t health;

	private:
		const Size SIZE = Size(1, 1);
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;
		uint16_t tile_id;
		uint8_t tile_index;
		Point position;
		Point screen_position;
		Point attack_position; //The position at which the attack animation is done
		Size spritesheet_size;
		bool attacking;
		bool moving;

		void walk_to_attack_position();
	};
}