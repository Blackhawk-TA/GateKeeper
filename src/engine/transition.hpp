//
// Created by daniel on 04.09.21.
//

#pragma once
#include "../utils/utils.hpp"

namespace transition {
	bool in_progress();
	void draw();
	void init();
	void start(std::function<void()> callback);
}
