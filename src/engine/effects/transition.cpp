//
// Created by daniel on 04.09.21.
//

#include "transition.hpp"

using namespace blit;

namespace transition {
	TransitionState state = INACTIVE;
	uint8_t black_out_time = 250;
	uint8_t transition_steps = 5;
	uint8_t transition_alpha = 0;
	uint32_t delta_time_fade_in = 0;
	uint32_t delta_time_fade_out = 0;
	std::function<void()> transition_callback;

	void update(uint32_t time) {
		switch (state) {
			case INACTIVE:
				return;
			case FADING_IN:
				if (transition_alpha + transition_steps < 255) {
					transition_alpha += transition_steps;
				} else {
					delta_time_fade_in = time;
					transition_alpha = 255;
					state = BLACKED_OUT;
				}
				break;
			case BLACKED_OUT:
				if (delta_time_fade_in + black_out_time >= time) {
					transition_callback();
					delta_time_fade_out = time;
					state = CALLBACK_EXECUTED;
				}
				break;
			case CALLBACK_EXECUTED:
				if (delta_time_fade_out + black_out_time >= time) {
					state = FADING_OUT;
				}
				break;
			case FADING_OUT:
				if (transition_alpha - transition_steps >= 0) {
					transition_alpha -= transition_steps;
				} else {
					transition_alpha = 0;
					state = INACTIVE;
				}
				break;
		}
	}

	bool in_process() {
		return state != INACTIVE;
	}

	void draw() {
		screen.pen = Pen(0, 0, 0, transition_alpha);
		screen.rectangle(Rect(0, 0, screen.bounds.w, screen.bounds.h));
	}

	void start(std::function<void()> callback) {
		transition_callback = std::move(callback);
		state = FADING_IN;
	}
}
