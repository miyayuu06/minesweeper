#pragma once
#include <vector>
#include <array>

namespace MS {
	class Board {
	public:
		const std::array<int, 3> sizes = { 9, 16, 24 };
		const std::array<int, 3> mines = { 10, 40, 99 };

		Board();
		void clear(int mode);
		void introduceBombs(int mode, int x, int y);
		int selectedCell(int mode, int x, int y, bool right);
		void BFS(int mode, int x, int y);

		int count(int mode, int x, int y);

		int update(int mode, float x, float y, bool right);

		void print();
		int value(int x, int y);

	private:
		bool gameStarted;
		int mode;
		std::array<int, 2> positionParser(int mode, float x, float y);

		std::vector<std::vector<int>> cells;
	};
}