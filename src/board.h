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
		void clearAll();
		void introduceBombs(int mode, float x, float y);
		int selectedCell(int mode, int x, int y);
		void BFS(int mode, int x, int y);

		int count(int mode, int x, int y);

		int update(int mode, float x, float y);

		void print();

	private:
		bool gameStarted;
		std::array<int, 2> positionParser(int mode, float x, float y);

		std::vector<std::vector<int>> easy;
		std::vector<std::vector<int>> med;
		std::vector<std::vector<int>> hard;
	};
}