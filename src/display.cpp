#include "display.h"
#include <iostream>

#define SDL_MAIN_HANDLED

namespace GOL {
	Display::Display() {
		desp = 10;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		if (!SDL_CreateWindowAndRenderer("Conway's Game of Life", size * desp, size * desp, SDL_WINDOW_OPENGL, &window, &renderer)) {
			std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
		}
		SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
	}

	Display::~Display() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Display::update() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		/*for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (!current.cell[i][j]) {
					pixel = { (float)desp * j, (float)desp * i, (float)desp, (float)desp };
					SDL_RenderFillRect(renderer, &pixel);
				}
			}
		}

		SDL_RenderPresent(renderer);
		next.nextGen(current);
		current = next;*/
	}

	std::string Display::print() {
		/*std::string ans = "";
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ans += (current.cell[i][j]) ? '-' : ' ';
			}
			ans += "\n";
		}
		next.nextGen(current);
		current.cell = next.cell;
		return ans;*/
		return "";
	}
}