//
// Created by daniel on 04.09.21.
//

#include "transition.hpp"

using namespace blit;

bool fading_in = true;
Timer *transition_timer;
uint8_t default_timer_duration = 7;
uint8_t transition_alpha = 0;
std::function<void()> transition_callback;

void fade(Timer &timer) {
	uint8_t transition_steps = 10;

	if (fading_in) {
		if (transition_alpha + transition_steps < 255) {
			transition_alpha += transition_steps;
		} else {
			transition_alpha = 255;
			timer.duration = 250;
			fading_in = false;

			transition_callback();
		}
	} else {
		timer.duration = default_timer_duration;
		if (transition_alpha - transition_steps >= 0) {
			transition_alpha -= transition_steps;
		} else {
			//Reset transition
			transition_alpha = 0;
			timer.stop();
			fading_in = true;
		}
	}
}

bool transition::in_progress() {
	return transition_timer->is_running();
}

void transition::draw() {
	screen.pen = Pen(0, 0, 0, transition_alpha);
	screen.rectangle(Rect(0, 0, screen.bounds.w, screen.bounds.h));
}

void transition::init() {
	transition_timer = new Timer();
	transition_timer->init(fade, default_timer_duration, -1);
}

void transition::start(std::function<void()> callback) {
	transition_callback = std::move(callback);
	transition_timer->start();
}
