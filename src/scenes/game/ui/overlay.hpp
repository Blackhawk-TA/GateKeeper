//
// Created by Daniel Peters on 12.04.21.
//

#pragma once
#include "32blit.hpp"

namespace game::overlay {
	void draw_statusbar();
	void draw_time();
	void draw_debug(const std::string& info);
}
