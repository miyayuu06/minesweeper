#include "board.h"
#include <iostream>

namespace MS {
	Board::Board() : cells(16, std::vector<int>(16, 0)), mode(2) {
		srand(time(nullptr));
	}

	void Board::clear(int m) {
		mode = m; gameStarted = false;
		cells.assign(sizes[mode - 1], std::vector<int>(sizes[mode - 1], 0));
	}

	int Board::value(int x, int y) {
		return cells[x][y];
	}

	void Board::introduceBombs(int mode, int x, int y) {
		if (x != -1) {
			int n = mines[mode - 1];
			int s = sizes[mode - 1];
			while (n) {
				int i = rand() % s;
				int j = rand() % s;
				if (cells[i][j] == 0 && (abs(x - i) >= 2 && abs(y - j) >= 2)) {
					cells[i][j] = 9;
					n--;
				}
			}
			gameStarted = true;
			BFS(mode, x, y);
		}
	}

	int Board::selectedCell(int mode, int x, int y, bool right) {
		if (x < -1) {
			return 1;
		}

		if (right) {
			if (cells[x][y] == 9) {
				cells[x][y] = 10;
			}
			else if (cells[x][y] == 0) {
				cells[x][y] = 11;
			}
			else if (cells[x][y] == 10) {
				cells[x][y] = 9;
			}
			else if (cells[x][y] == 11) {
				cells[x][y] = 0;
			}
			return 1;
		}

		if (cells[x][y] == 9) {
			return 0;
		}

		BFS(mode, x, y);
		return 1;
	}

	void Board::BFS(int mode, int x, int y) {
		int size = sizes[mode - 1];
		if (x < size && x >= 0 && y < size && y >= 0) {

			if (cells[x][y] != 0) {
				return;
			}

			cells[x][y] = -1;

			int c = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (!(i == 0 && j == 0)) {
						c += count(mode, x + i, y + j);
					}
				}
			}

			if (c > 0) {
				cells[x][y] = c;
			}
			else {
				cells[x][y] = -1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						BFS(mode, x + i, y + j);
					}
				}
			}
		}
	}

	int Board::count(int mode, int x, int y) {
		if (x < 0 || y < 0 || x >= sizes[mode - 1] || y >= sizes[mode - 1]) {
			return 0;
		}
		return cells[x][y] == 9;
	}

	int Board::update(int mode, float x, float y, bool right) {
		std::array<int, 2> pressedCell = positionParser(mode, x, y);
		if (!gameStarted) {
			if (!right) {
				introduceBombs(mode, pressedCell[0], pressedCell[1]);
			}
			return 1;
		}
		return selectedCell(mode, pressedCell[0], pressedCell[1], right);
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
		for (int i = 0; i < cells.size(); i++) {
			for (int j = 0; j < cells.size(); j++) {
				std::cout << cells[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
}
