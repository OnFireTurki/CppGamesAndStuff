#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

#pragma region SudokuSolver

namespace Cpp {
	const unsigned short SIZE = 9;
	typedef std::array<std::array<int, SIZE>, SIZE> SudokuBoard;

	SudokuBoard OurBoard{ {
  {7, 0, 2, 0, 5, 0, 6, 0, 0},
		{0, 0, 0, 0, 0, 3, 0, 0, 0},
		{1, 0, 0, 0, 0, 9, 5, 0, 0},
		{8, 0, 0, 0, 0, 0, 0, 9, 0},
		{0, 4, 3, 0, 0, 0, 7, 5, 0},
		{0, 9, 0, 0, 0, 0, 0, 0, 8},
		{0, 0, 9, 7, 0, 0, 0, 0, 5},
		{0, 0, 0, 2, 0, 0, 0, 0, 0},
		{0, 0, 7, 0, 4, 0, 2, 0, 3}
		} };
	// 0, 0, 0, 0, 0, 0, 0, 0, 0

	void PrintTheBoard(const SudokuBoard& board) {
		for (int i = 0; i < SIZE; i++) {
			if (i != 0 && !(i % 3))
				std::cout << "====+=====+====\n";
			for (int j = 0; j < SIZE; j++) {
				if (j != 0 && !(j % 3))
					std::cout << " | ";
				std::cout << board[i][j];
			}
			std::cout << "\n";
		}

	};

	bool InARow(const SudokuBoard& board, int item, int row) {
		for (int i = 0; i < SIZE; i++) {
			if (board[row][i] == item)
				return true;
		}
		return false;
	}

	bool InAColumn(const SudokuBoard& board, int item, int column) {
		for (int i = 0; i < SIZE; i++) {
			if (board[i][column] == item)
				return true;
		}
		return false;
	}

	bool InABox(const SudokuBoard& board, int item, int row, int column) {
		int ourR = row - row % 3;
		int ourC = column - column % 3;
		for (int i = ourR; i < ourR + 3; i++) {
			for (int j = ourC; j < ourC + 3; j++) {
				if (board[i][j] == item)
					return true;
			}
		}
		return false;
	}

	bool IsThisValid(const SudokuBoard& board, int item, int row, int column) {
		return !InARow(board, item, row) && !InAColumn(board, item, column) && !InABox(board, item, row, column);
	}

	bool SolveTheBoard(SudokuBoard& board) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (board[i][j] == 0) {
					for (int k = 1; k <= SIZE; k++) {
						if (IsThisValid(board, k, i, j)) {
							board[i][j] = k;
							if (SolveTheBoard(board))
								return true;
							else
								board[i][j] = 0;
						}
					}
					// After trying all numbers from one to nine and none of them have worked
					// This mean that we cant continue with this board, unable to solve
					return false;
				}
			}
		}
		return true;
	}

}

#pragma endregion



int main()
{
	Cpp::PrintTheBoard(Cpp::OurBoard);
	std::cout << "111111111111111111111111111\n";
	std::cout << (bool)Cpp::SolveTheBoard(Cpp::OurBoard) << "\n";
	Cpp::PrintTheBoard(Cpp::OurBoard);
	std::cin.get();
}
