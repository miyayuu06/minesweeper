#include "timer.h"

namespace MS {
	Timer::Timer() : value(0), running(false), start(0) {}

	Timer::~Timer() {}

	void Timer::reset() {
		value = 0;
		start = time(nullptr);
		running = false;
	}

	void Timer::tick() {
		if (running) {
			time_t now = time(nullptr);
			if (now > start) {
				value++;
				start = now;
			}

			if (value > limit) {
				value = limit;
			}
		}
	}

	void Timer::pause() {
		if (running) {
			tick();
		}
		running = false;
	}
	void Timer::resume() {
		running = true;
		start = time(nullptr);
	}
	int Timer::val() {
		return value;
	}

	bool Timer::isRunning() const {
		return running;
	}
}