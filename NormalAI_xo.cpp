#include <iostream>
#include <string>
#include <limits.h>
#include <unordered_map>
#include <array>

#define ai "X"
#define SIZE 3

typedef std::array<std::array<std::string, SIZE>, SIZE> XOboard;


std::unordered_map<std::string, int> s = {
	{"X", 1}, // maximizer player
	{"O", -1},// minimizer player
	{"draw", 0},
};



XOboard InitBoard() {
	XOboard  board{ {} };
	int n = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = std::to_string(++n);
		}
	}
	return board;
}

void printboard(XOboard& x) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << x[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

bool makemove(XOboard& x, std::string& player, std::string& move) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (x[i][j] == move) {
				x[i][j] = player;
				return true;
			}
		}

	}
	return false;
}


int checkEmpty(XOboard& x) {
	int res = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (x[i][j] != "O" && x[i][j] != "X")
				res++;
	return res;
}

std::string checkwinner(XOboard& board) {
	std::string a[2] = { {"O"}, {"X"} };
	for (std::string player : a) {
		for (int i = 0; i < SIZE; i++) {
			if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
				return player;
			}
		}
		if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
			return player;
		}
	}
	return checkEmpty(board) > 0 ? "" : "draw";
}

int minimax(XOboard& x, int depth, bool maximizing) {
	std::string p = maximizing ? "X" : "O";
	std::string res2 = checkwinner(x);
	
	if (res2 != "") {
		return s[res2];
	}
	if (depth >= 9) {
		return 0;
	}
	else {
		if (maximizing) {
			int res = INT_MIN;
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (x[i][j] != "O" && x[i][j] != "X") {
						std::string temp = x[i][j];
						x[i][j] = p;
						int attemptresult = minimax(x, depth + 1, 0);
						x[i][j] = temp;
						res = (std::max(res, attemptresult));
					}
				}
			}
			return res;
		}
		else {
			int res = INT_MAX;
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (x[i][j] != "O" && x[i][j] != "X") {
						std::string temp = x[i][j];
						x[i][j] = p;
						int attemptresult = minimax(x, depth + 1, 1);
						x[i][j] = temp;
						res = std::min(res, attemptresult);
					}
				}
			}
			return res;
		}
	}

}

void Aimove(XOboard& x, int movenum) {
	int res = INT_MIN;
	std::pair<int, int> move = { -1, -1 };
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (x[i][j] != "O" && x[i][j] != "X") {
				std::string temp = x[i][j];
				x[i][j] = ai;
				int attemptresult = minimax(x, movenum + 1, 0);
				x[i][j] = temp;
				if (attemptresult > res) {
					res = attemptresult;
					move.first = i;
					move.second = j;
				}
			}
		}
	}
	if (move.first >= 0 && move.second >= 0)
		x[move.first][move.second] = ai;
}

int main()
{
	XOboard xboard = InitBoard();
	std::string player = "O", move;
	std::cout << "Welcome.\n";
	int moves = 0;
	while (moves < 9 && checkwinner(xboard) == "")
	{
	retry:
		system("cls");
		printboard(xboard);
		if (moves % 2 != 0) {
			std::cout << player << " - make your move (1..9): ";
			std::getline(std::cin, move);
			if (!makemove(xboard, player, move))
				goto retry;
		}
		else
			Aimove(xboard, moves);
		moves++;
		//	player = player == "X" ? "O" : "X";
	}
	std::string g = checkwinner(xboard);
	system("cls");
	printboard(xboard);
	if (g != "draw")
		std::cout << "The winner is player : " << g << std::endl;
	else
		std::cout << "It is a draw !" << std::endl;
	return 0;

}
