//
// Created by daniel on 28.02.21.
//

#pragma once
#include "utils.hpp"

using namespace blit;

namespace map {
	enum TileFlags {
		SOLID = 1
	};

	void create();
	void draw(Point offset);
	void set_flags(TileFlags flag, const std::vector<uint8_t> &tiles);
	uint8_t get_flag(Point p);
}
