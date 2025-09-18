#include "display.h"
#include <iostream>

#define SDL_MAIN_HANDLED

namespace MS {
	Display::Display() {
		mode = 2;

		board.clearAll();

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

	void Display::update(bool clicked, float x, float y) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 17, 168, 80, 255);
		if (x >= 1500 && x <= 1800) {
			if (y >= 200 && y <= 300 && !clicked) {
				mode = 1;
				board.clearAll();
				SDL_SetRenderDrawColor(renderer, 7, 158, 70, 255);
			}
		}
		pixel = { (float) 1500, (float) 200, (float) 300, (float) 100};
		SDL_RenderFillRect(renderer, &pixel);

		SDL_SetRenderDrawColor(renderer, 215, 222, 18, 255);
		if (x >= 1500 && x <= 1800) {
			if (y >= 500 && y <= 600 && !clicked) {
				mode = 2;
				board.clearAll();
				SDL_SetRenderDrawColor(renderer, 205, 212, 8, 255);
			}
		}
		pixel = { (float) 1500, (float) 500, (float) 300, (float) 100 };
		SDL_RenderFillRect(renderer, &pixel);

		SDL_SetRenderDrawColor(renderer, 222, 18, 18, 255);
		if (x >= 1500 && x <= 1800) {
			if (y >= 800 && y <= 900 && !clicked) {
				mode = 3;
				board.clearAll();
				SDL_SetRenderDrawColor(renderer, 202, 8, 8, 255);
			}
		}
		pixel = { (float) 1500, (float) 800, (float) 300, (float) 100 };
		SDL_RenderFillRect(renderer, &pixel);

		SDL_RenderPresent(renderer);
	}

	int Display::print() {
		return mode;
	}
}