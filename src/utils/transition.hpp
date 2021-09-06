//
// Created by daniel on 04.09.21.
//

#pragma once
#include "utils.hpp"

using namespace blit;

namespace transition {
	bool in_progress();
	void draw();
	void start(std::function<void()> callback);
}
