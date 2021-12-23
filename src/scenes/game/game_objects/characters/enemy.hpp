//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

class Enemy : public Character {
private:
	static const uint16_t ANIMATION_BASE_DELAY = 2500;
	static const uint16_t ANIMATION_VARIANCE = 2000;
	uint32_t last_turn;
	uint32_t animation_delay;
	bool turn;
	bool in_action;

	void set_state(uint8_t new_state) override;
	bool player_interact() override;
	bool player_in_sightline();
	void walk_to_player();
	void trigger_cut_scene();
	void walk_to_next_tile(MovementDirection direction);

public:
	explicit Enemy(map::MapSections map_section, Point position, uint16_t tile_id, MovementDirection direction, bool turn = true);
	~Enemy() override = default;
	void update(uint32_t time) override;
	void update_state(Point next_position) override;
};
