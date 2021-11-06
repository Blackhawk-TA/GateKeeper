//
// Created by daniel on 06.11.21.
//

#pragma once
#include "utils.hpp"

namespace game_time {
	void init();
	void update(uint32_t time);
	void load(uint32_t time);
	uint32_t get_time();
	std::string get_formatted();
}
