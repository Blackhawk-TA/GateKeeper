//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

class Villager : public Character {
private:
	uint32_t last_turn;
	uint32_t animation_delay;
	std::string message;

	void set_state(uint8_t new_state) override;

public:
	explicit Villager(map::MapSections map_section, Point position, uint16_t tile_id, MovementDirection direction, std::string message);
	~Villager() override = default;
	void update(uint32_t time) override;
	void update_state(Point next_position) override;
	bool player_interact() override;
	void close_textbox() override;
};
