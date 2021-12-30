//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

namespace game {
	class Enemy : public Character {
	private:
		void set_state(uint8_t new_state) override;
		bool player_interact() override;
		void trigger_cut_scene() override;

	public:
		explicit Enemy(map::MapSection map_section, Point position, uint16_t tile_id, MovementDirection direction, bool turn = true);
		~Enemy() override = default;
		void update(uint32_t time) override;
		void update_state(Point next_position) override;
	};
}