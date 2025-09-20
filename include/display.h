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
		void update(float x, float y, bool right);

		int print();
		void renderBoard(int mode);

	private:
		const std::vector<int> r = { 220, 170,  25,  25,  13,   0, 123,  60, 128,  60, 200, 0, 0 };
		const std::vector<int> g = { 220, 170, 118,  25,  51, 123,  46, 108,   0,  60,   0, 0, 0 };
		const std::vector<int> b = { 220, 170, 210, 118, 217, 123,  19,  60, 128,  60,   0, 0, 0 };
		int mode;

		int width;
		int height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;

		Board board;
	};
}