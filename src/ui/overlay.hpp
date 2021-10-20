//
// Created by Daniel Peters on 12.04.21.
//

#pragma once
#include "32blit.hpp"

namespace overlay {
	void draw_statusbar(uint8_t health);
	void draw_fps(uint32_t &ms_start, uint32_t &ms_end);
}
