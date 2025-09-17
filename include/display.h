#pragma once
#include <string>

#include "SDL3/SDL.h"

namespace GOL {
	class Display {
	public:
		Display();
		~Display();

		void s();

		void update();

		std::string print();

	private:
		int size;
		int desp;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;


		std::pair<int, int> antPos;

	};
}