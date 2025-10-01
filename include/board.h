#pragma once
#include <vector>
#include <array>
#include <coordinates.h>

namespace MS {
	class Board {
	public:
		const std::array<int, 3> sizes = { 9, 16, 24 };
		const std::array<int, 3> mines = { 10, 40, 99 };

		Board();
		void clear(int mode);
		void introduceBombs(int x, int y);
		int selectedCell(int x, int y, bool right);
		void BFS(int x, int y);
		int count(int x, int y);
		int update(float x, float y, bool right);

		int value(int x, int y);

	private:
		const Coordinates topLeft = { 460, 100 };
		const Coordinates bottomRight = { 1460, 1100 };
		int filled;
		bool gameStarted;
		bool validGame;
		int mode;
		std::vector<std::vector<int>> cells;

		std::array<int, 2> positionParser(float x, float y);
	};
}