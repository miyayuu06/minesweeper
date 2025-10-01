#include "board.h"
#include <iostream>

namespace MS {
	Board::Board() : cells(16, std::vector<int>(16, 0)), mode(2), filled(40), validGame(true), gameStarted(false) {
		srand(time(nullptr));
	}

	void Board::clear(int m) {
		mode = m; gameStarted = false; validGame = true;
		filled = mines[m - 1];
		cells.assign(sizes[mode - 1], std::vector<int>(sizes[mode - 1], 0));
	}

	int Board::value(int x, int y) {
		return cells[x][y];
	}

	void Board::introduceBombs(int x, int y) {
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
			BFS(x, y);
		}
	}

	int Board::selectedCell(int x, int y, bool right) {
		if (x < -1) {
			return 1;
		}

		if (right) {
			if (cells[x][y] == 9) {
				filled--;
				if (!filled) {
					for (int i = 0; i < sizes[mode - 1]; i++) {
						for (int j = 0; j < sizes[mode - 1]; j++) {
							if (cells[i][j] == 10) {
								cells[i][j] = 12;
							}
						}
					}
					cells[x][y] = 12; validGame = false; // Player wins
					return 2; 
				}
				else {
					cells[x][y] = 10;
				}
			}
			else if (cells[x][y] == 0) {
				cells[x][y] = 11;
			}
			else if (cells[x][y] == 10) {
				cells[x][y] = 9;
				filled++;
			}
			else if (cells[x][y] == 11) {
				cells[x][y] = 0;
			}
			return 1;
		}

		if (cells[x][y] == 9) {
			for (int i = 0; i < sizes[mode - 1]; i++) {
				for (int j = 0; j < sizes[mode - 1]; j++) {
					if (cells[i][j] == 9 || cells[i][j] == 10) {
						cells[i][j] = 13;
					}
				}
			}
			validGame = false; // Player fails
			return 0;
		}

		BFS(x, y);
		return 1;
	}

	void Board::BFS(int x, int y) {
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
						c += count(x + i, y + j);
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
						BFS(x + i, y + j);
					}
				}
			}
		}
	}

	int Board::count(int x, int y) {
		if (x < 0 || y < 0 || x >= sizes[mode - 1] || y >= sizes[mode - 1]) {
			return 0;
		}
		return cells[x][y] == 9 || cells[x][y] == 10;
	}

	int Board::update(float x, float y, bool right) {
		if (!validGame) {
			return 3;
		}
		std::array<int, 2> pressedCell = positionParser(x, y);
		if (pressedCell[0] == -1 || pressedCell[1] == -1) {
			return 3;
		}
		if (!gameStarted) {
			if (!right) {
				introduceBombs(pressedCell[0], pressedCell[1]);
			}
			return 1;
		}
		return selectedCell(pressedCell[0], pressedCell[1], right);
	}

	std::array<int, 2> Board::positionParser(float x, float y) {
		int size = sizes[mode - 1];

		if (x < topLeft.x || x > bottomRight.x || y < topLeft.y || y > bottomRight.y) {
			return { -1, -1 };
		}

		float cell = 1000.0f / size;

		int col = (x - 460) / cell;
		int row = (y - 100) / cell;

		return { row, col };
	}
}
