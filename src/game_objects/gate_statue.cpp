//
// Created by D069765 on 26.10.2021.
//

#include "gate_statue.hpp"

GameStatue::GameStatue(Point position, map::MapSections map_section) {
	GameStatue::position = position;
	GameStatue::map_section = map_section;
}

bool GameStatue::check_collision(Point next_position) {
	if (map::get_section() != map_section) {
		return false;
	}

	return false;
}

void GameStatue::draw() {
	if (map::get_section() != map_section) {
		return;
	}
}

bool GameStatue::interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	return false;
}

void GameStatue::update_state(Point next_position) {
	if (map::get_section() != map_section) {
		return;
	}
}

void GameStatue::set_state(uint8_t new_state) {

}
