#pragma once
#include <string>

#include "SDL3/SDL.h"
#include "board.h"
#include "audio.h"

namespace MS {
	class Display {
	public:
		Display();
		~Display();

		void render(float x, float y);
		void update(float x, float y, bool right);

		int print();

	private:
		const std::vector<int> r = { 220, 170,  25,  25,  13,   0, 123,  60, 128,  60, 200, 0, 0 };
		const std::vector<int> g = { 220, 170, 118,  25,  51, 123,  46, 108,   0,  60,   0, 0, 0 };
		const std::vector<int> b = { 220, 170, 210, 118, 217, 123,  19,  60, 128,  60,   0, 0, 0 };
		const std::vector<std::string> sounds = {"sfx/lose.mp3", "sfx/click.mp3", "sfx/win.mp3", ""};
		const std::vector<std::string> buttons = { "sprites/easy.png", "sprites/medium.png", "sprites/hard.png"};

		void renderBoard(int mode);
		void renderButtons(float x, float y);

		int mode;

		int width;
		int height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;
		SDL_Texture* icons[15];
		SDL_Texture* buttonTex[3];;
		Audio buzzer;

		Board board;
	};
}