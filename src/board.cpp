#include "board.h"
#include <iostream>

namespace MS {
	Board::Board() : easy(9, std::vector<int>(9, 0)),
		med(16, std::vector<int>(16, 0)),
		hard(24, std::vector<int>(24, 0)) {
		srand(NULL);
	}

	void Board::clear(int mode) {
		for (int i = 0; i < sizes[mode - 1]; i++) {
			for (int j = 0; j < sizes[mode - 1]; j++) {
				if (mode == 1) {
					easy[i][j] = 0;
				}
				else if (mode == 2) {
					med[i][j] = 0;
				}
				else {
					hard[i][j] = 0;
				}
			}
		}
	}

	void Board::clearAll() {
		clear(1);
		clear(2);
		clear(3);
		gameStarted = false;
	}

	void Board::introduceBombs(int mode, int x, int y) {
		if (x != -1) {
			auto& ref = (mode == 1) ? easy : (mode == 2) ? med : hard;
			ref[x][y] = -1;
			int n = mines[mode - 1];
			int s = sizes[mode - 1];
			while (n) {
				int i = rand() % s;
				int j = rand() % s;
				if (ref[i][j] == 0) {
					ref[i][j] = 9;
					n--;
				}
			}

			if (mode == 1) {
				easy = ref;
			}
			else if (mode == 2) {
				med = ref;
			}
			else {
				hard = ref;
			}

		}
	}

	int Board::selectedCell(int mode, int x, int y) {
		if (x < -1) {
			return 1;
		}

		if ((mode == 1 && easy[x][y] == 9) || (mode == 2 && med[x][y] == 9) || (mode == 3 && hard[x][y] == 9)) {
			return 0;
		}

		if (mode == 1) {
			easy[x][y] = -1;
		}
		else if (mode == 2) {
			med[x][y] = -1;
		}
		else {
			hard[x][y] = -1;
		}

		BFS(mode, x, y);
		return 1;
	}

	void Board::BFS(int mode, int x, int y) {
		int size = sizes[mode - 1];
		auto& ref = (mode == 1) ? easy : (mode == 2) ? med : hard;
		if (x < size && x >= 0 && y < size && y >= 0) {
			if (ref[x][y] != -1) {
				return;
			}

			int c = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					c += (i != 0 && j != 0) ? count(mode, x + i, y + j) : 0;
				}
			}
			ref[x][y] = c;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					BFS(mode, x + i, y + j);
				}
			}
		}
	}

	int Board::count(int mode, int x, int y) {
		if (x < 0 || y < 0 || x >= sizes[mode - 1] || y >= sizes[mode - 1]) {
			return 0;
		}
		return (mode == 1) ? (easy[x][y] == 9) :
			(mode == 2) ? (med[x][y] == 9) :
			(mode == 3) ? (hard[x][y] == 9) : 0;
	}

	int Board::update(int mode, float x, float y) {
		std::array<int, 2> pressedCell = positionParser(mode, x, y);
		if (!gameStarted) {
			introduceBombs(mode, pressedCell[0], pressedCell[1]);
			return 1;
		}
		return selectedCell(mode, pressedCell[0], pressedCell[1]);
	}

	std::array<int, 2> Board::positionParser(int mode, float x, float y) {
		int size = sizes[mode - 1];

		if (x < 250 || x > 1250 || y < 100 || y > 1100) {
			return { -1, -1 };
		}

		float cell = 1000.0f / size;

		int col = (x - 250) / cell;
		int row = (y - 100) / cell;

		return { row, col };
	}

	void Board::print() {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				std::cout << med[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << gameStarted;
	}
}
