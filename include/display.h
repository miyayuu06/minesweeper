#pragma once
#include <string>

#include "SDL3/SDL.h"
#include "SDL3/SDL_ttf.h"
#include "board.h"
#include "audio.h"
#include "timer.h"

namespace MS {
	class Display {
	public:
		Display();
		~Display();

		void render(float x, float y);
		void update(float x, float y, bool right);

	private:
		const Coordinates topLeft = { 460, 100 };
		const Coordinates bottomRight = { 1460, 1100 };
		const Coordinates buttonTopLeft = { 710, 200 };
		const Coordinates buttonBottomRight = { 1210, 1100 };
		const Coordinates buttonSize = { 500, 200 };
		const Coordinates menuPos = { 20, 70 };
		const Coordinates bestScorePos = { 100, 400 };
		const Coordinates timerPos = { 90, 200 };

		const std::vector<int> r = { 220, 170,  25,  25,  13,   0, 123,  60, 128,  60, 200, 0, 0 };
		const std::vector<int> g = { 220, 170, 118,  25,  51, 123,  46, 108,   0,  60,   0, 0, 0 };
		const std::vector<int> b = { 220, 170, 210, 118, 217, 123,  19,  60, 128,  60,   0, 0, 0 };
		const std::vector<std::string> sounds = {"sfx/lose.mp3", "sfx/click.mp3", "sfx/win.mp3", ""};
		
		//const std::vector<std::string> buttons = { "easy.png", "normal.png", "hard.png" };
		
		std::vector<int> buttonr = { 80, 200, 180 };
		std::vector<int> buttong = { 160, 180, 50 };
		std::vector<int> buttonb = { 80, 80, 50 };
		std::vector<std::string> buttonText = { " EASY ", "MEDIUM", " HARD " };

		std::vector<int> best = { 999, 999, 999 };

		void renderBoard(int mode);
		void renderButtons(float x, float y);
		void renderTimer(int time);
		void renderBestScore(int mode);
		void renderMenuButton();

		int mode;
		bool menu;

		Uint64 gameStartTime = 0;
		void toggleToMenu();

		int width;
		int height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_FRect pixel;
		SDL_Texture* icons[15];
		SDL_Texture* menuIcon;

		SDL_Texture* buttonTex[3];
		SDL_Surface* textSurface = nullptr;
		SDL_Texture* textTex = nullptr;
		SDL_Color textColor = { 0, 0, 0, 255 };
		SDL_Color buttonTextColor = { 255, 255, 255, 255 };
		SDL_FRect renderQuad = { 1500.0f, 100.0f, 0.0f, 0.0f };
		TTF_Font* font = nullptr;
		TTF_Font* smallFont = nullptr;
		TTF_Font* buttonFont = nullptr;
		
		Timer timer;
		Audio buzzer;

		Board board;
	};
}