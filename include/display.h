#pragma once
#include <string>

#include "SDL3/SDL.h"
#include "board.h"

namespace MS {
	class Display {
	public:
		Display();
		~Display();

		void update(bool clicked, float x, float y);

		int print();

	private:
		int mode;

		int width;
		int height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;

		Board board;
	};
}