#pragma once
#include <time.h>

namespace MS {
	class Timer {
	public:
		Timer();
		~Timer();

		void reset();
		void tick();
		void pause();
		void resume();
		int val();
		bool isRunning() const;

	private:
		int value;
		time_t start;
		const int limit = 999;

		bool running = false;
	};
}