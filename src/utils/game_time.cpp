//
// Created by daniel on 06.11.21.
//

#include <sstream>
#include <iomanip>
#include "game_time.hpp"

const uint32_t ONE_HOUR_IN_MS = 360000;
const uint16_t ONE_MINUTE_IN_MS = 60000;
const uint16_t ONE_SECOND_IN_MS = 1000;

uint32_t time_passed = 0;
uint32_t last_time = 0;

void game_time::init() {
	time_passed = 0;
	last_time = 0;
}

void game_time::update(uint32_t time) {
	if (last_time == 0) {
		last_time = time;
	} else {
		time_passed += time - last_time;
		last_time = time;
	}
}

void game_time::load(uint32_t time) {
	time_passed = time;
}

uint32_t game_time::get_time() {
	return time_passed;
}

std::string game_time::get_formatted() {
	std::stringstream formatted_time;
	uint32_t time_copy = time_passed;

	uint16_t hrs = time_copy / ONE_HOUR_IN_MS;
	time_copy -= hrs * ONE_HOUR_IN_MS;

	uint16_t min = time_copy / ONE_MINUTE_IN_MS;
	time_copy -= min * ONE_MINUTE_IN_MS;

	uint16_t sec = time_copy / ONE_SECOND_IN_MS;

	formatted_time << std::setfill('0') << std::setw(2) << hrs << ':' << std::setw(2) << min << ':' << std::setw(2) << sec;

	return formatted_time.str();
}
