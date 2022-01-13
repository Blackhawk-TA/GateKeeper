//
// Created by daniel on 04.09.21.
//

#pragma once
#include "../../utils/utils.hpp"

namespace transition {
	enum TransitionState {
		INACTIVE = 0,
		FADING_IN = 1,
		BLACKED_OUT = 2,
		CALLBACK_EXECUTED = 3,
		FADING_OUT = 4,
	};

	bool in_process();
	void draw();
	void update(uint32_t time);
	void start(std::function<void()> callback);
}
