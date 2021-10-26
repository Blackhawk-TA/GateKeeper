//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "game_object_interface.hpp"
#include "../engine/map.hpp"

class GameStatue : public IGameObject {
private:
	Point position;
	map::MapSections map_section;

	void set_state(uint8_t new_state) override;

public:
	explicit GameStatue(Point position, map::MapSections map_section);
	~GameStatue() override = default;
	bool check_collision(Point next_position) override;
	void draw() override;
	bool interact() override;
	void update_state(Point next_position) override;
};
