//
// Created by D069765 on 20.10.2021.
//

#pragma once
#include "../utils.hpp"

namespace options {
	const uint8_t OPTIONS_DATA_SLOT = 0;
	const uint8_t MAX_SAVES = 3;

	//Global settings variables
	extern bool show_fps;
	extern bool show_time;
	extern uint8_t save_count;
	extern uint8_t active_tmp_save;

	void save();
	void load();
}
