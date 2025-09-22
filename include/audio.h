#pragma once
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <string>

namespace MS {
	class Audio {
	public:
		Audio();
		~Audio();
		void playMP3(const std::string filename);

	private:
		SDL_AudioStream* _stream;
	};
}