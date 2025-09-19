#include "display.h"
#include <iostream>

#define SDL_MAIN_HANDLED

namespace MS {
	Display::Display() {
		mode = 1;

		board.clear(mode);

		width = 1920;
		height = 1200;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		if (!SDL_CreateWindowAndRenderer("Yuna's Minesweeper", width, height, SDL_WINDOW_OPENGL, &window, &renderer)) {
			std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
		}
		SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
	}

	Display::~Display() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Display::render(float x, float y) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		renderBoard(mode);

		SDL_SetRenderDrawColor(renderer, 17, 168, 80, 255);
		if (x >= 1500 && x <= 1800) {
			if (y >= 200 && y <= 300) {
				SDL_SetRenderDrawColor(renderer, 7, 158, 70, 255);
			}
		}
		pixel = { (float) 1500, (float) 200, (float) 300, (float) 100};
		SDL_RenderFillRect(renderer, &pixel);

		SDL_SetRenderDrawColor(renderer, 215, 222, 18, 255);
		if (x >= 1500 && x <= 1800) {
			if (y >= 500 && y <= 600) {
				SDL_SetRenderDrawColor(renderer, 205, 212, 8, 255);
			}
		}
		pixel = { (float) 1500, (float) 500, (float) 300, (float) 100 };
		SDL_RenderFillRect(renderer, &pixel);

		SDL_SetRenderDrawColor(renderer, 222, 18, 18, 255);
		if (x >= 1500 && x <= 1800) {
			if (y >= 800 && y <= 900) {
				SDL_SetRenderDrawColor(renderer, 202, 8, 8, 255);
			}
		}
		pixel = { (float) 1500, (float) 800, (float) 300, (float) 100 };
		SDL_RenderFillRect(renderer, &pixel);

		SDL_RenderPresent(renderer);
	}

	void Display::update(float x, float y) {
		if (x >= 1500 && x <= 1800) {
			bool changed = false;
			if (y >= 200 && y <= 300) {
				mode = 1; changed = true;
			}
			if (y >= 500 && y <= 600) {
				mode = 2; changed = true;
			}
			if (y >= 800 && y <= 900) {
				mode = 3; changed = true;
			}
			if (changed) {
				board.clear(mode);
			}
		}
		else {
			board.update(mode, x, y);
		}
	}

	void Display::renderBoard(int mode) {
		int size = board.sizes[mode - 1];

		float cell = 1000.0f / size;

		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				float x = 250 + col * cell;
				float y = 100 + row * cell;

				pixel = { x, y, cell, cell };

				int cellContent = board.value(row, col) + 1;

				SDL_SetRenderDrawColor(renderer, r[cellContent], g[cellContent], b[cellContent], 255);

				SDL_RenderFillRect(renderer, &pixel);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderRect(renderer, &pixel);
			}
		}
	}

	int Display::print() {
		board.print();
		return mode;
	}
}