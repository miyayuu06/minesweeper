#pragma once
#include <string>

#include "SDL3/SDL.h"
#include "board.h"

namespace MS {
	class Display {
	public:
		Display();
		~Display();

		void render(float x, float y);
		void update(float x, float y);

		int print();
		void renderBoard(int mode);

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