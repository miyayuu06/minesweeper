#include "display.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <cassert>

#define SDL_MAIN_HANDLED

namespace MS {
	Display::Display() : pixel({}) {
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		mode = 2;

		board.clear(mode);

		width = 1920;
		height = 1200;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		if (!SDL_CreateWindowAndRenderer("Yuna's Minesweeper", width, height, SDL_WINDOW_OPENGL, &window, &renderer)) {
			std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
		}
		SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

		for (int i = -1; i <= 13; i++) {
			auto filename = "sprites/" + std::to_string(i) + ".png";
			icons[i+1] = IMG_LoadTexture(renderer, filename.c_str());
		}

		for (int i = 0; i < 3; i++) {
			buttonTex[i] = IMG_LoadTexture(renderer, buttons[i].c_str());
		}

		font = TTF_OpenFont("C:/Windows/Fonts/Stencil.ttf", 170);
		smallFont = TTF_OpenFont("C:/Windows/Fonts/Stencil.ttf", 60);
		if (font == NULL) {
			std::cout << "No font bro";
		}
	}

	Display::~Display() {
		for (auto& v : icons) {
			SDL_DestroyTexture(v);
		}
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_CloseFont(font);
	}

	void Display::render(float x, float y) {
		timer.tick();
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		renderBoard(mode);

		renderButtons(x, y);

		renderTimer(timer.val());

		renderBestScore(mode);

		SDL_RenderPresent(renderer);
	}

	void Display::update(float x, float y, bool right) {
		timer.tick();
		if (x >= 1500 && x <= 1800) {
			bool changed = false;
			for (int i = 0; i < 3; i++) {
				if ((y >= (200 + i * 200)) && (y <= (300 + i * 200))) {
					mode = i+1; changed = true; 
					break;
				}
			}
			if (changed) {
				board.clear(mode);
				timer.reset(); timer.pause();
			}
		}
		else {
			int noise = board.update(mode, x, y, right);
			if (noise == 1 || (noise == 3 && timer.isRunning())) {
				timer.resume();
			}
			if (noise == 2 || noise == 0) {
				timer.pause();
				if (noise == 2 && timer.val() < best[mode - 1]) {
					best[mode - 1] = timer.val();
				}
			}

			buzzer.playMP3(sounds[noise]);
		}
	}

	void Display::renderBoard(int mode) {
		int size = board.sizes[mode - 1];

		float cell = 1000.0f / size;

		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				float x = 250 + col * cell;
				float y = 100 + row * cell;

				SDL_FRect dst = { x, y, cell, cell };

				int cellValue = board.value(row, col);
				SDL_Texture* tex = icons[cellValue + 1];

				if (tex) SDL_RenderTexture(renderer, tex, nullptr, &dst);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderRect(renderer, &dst);
			}
		}
	}

	void Display::renderButtons(float x, float y) {
		for (int i = 0; i < 3; i++) {
			float opacity = 1.0f;

			float auxY = 200.f + ((float)i * 200.f);
			pixel = { 1500.f, auxY, 300.f, 100.f};

			if (x >= 1500 && x <= 1800) {
				if (y >= auxY && y <= (auxY + 100.f)) {
					opacity = 0.7f;
				}
			}

			SDL_SetTextureAlphaMod(buttonTex[i], static_cast<Uint8>(255 * opacity));
			SDL_RenderTexture(renderer, buttonTex[i], nullptr, &pixel);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderRect(renderer, &pixel);
		}
	}

	void Display::renderTimer(int time) {
		std::string timeToPrint = std::to_string(time);
		while (timeToPrint.length() < 3) {
			timeToPrint = "0" + timeToPrint;
		}

		textSurface = TTF_RenderText_Solid(font, timeToPrint.c_str(), 3, textColor);
		textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_DestroySurface(textSurface);
		renderQuad.x = 1500.0f; renderQuad.y = 750.0f;
		SDL_GetTextureSize(textTex, &(renderQuad.w), &(renderQuad.h)); 
		SDL_RenderTexture(renderer, textTex, NULL, &renderQuad);
	}

	void Display::renderBestScore(int mode) {
		std::string bestToPrint = "Best: ";
		if (best[mode - 1] != 999) {
			bestToPrint += std::to_string(best[mode - 1]);
			while (bestToPrint.length() < 9) {
				bestToPrint = bestToPrint.insert(6, "0");
			}
		}
		textSurface = TTF_RenderText_Solid(smallFont, bestToPrint.c_str(), bestToPrint.size(), textColor);
		textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_DestroySurface(textSurface);
		SDL_GetTextureSize(textTex, &(renderQuad.w), &(renderQuad.h));
		renderQuad.x = 1500.0f; renderQuad.y = 950.0f;
		SDL_RenderTexture(renderer, textTex, NULL, &renderQuad);
	}

	int Display::print() {
		board.print();
		return mode;
	}
}