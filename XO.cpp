#include <iostream>
#include <string>
#include <limits.h>
#include <unordered_map>
#include <array>

#define ai "X"
#define SIZE 3

typedef std::array<std::string, SIZE* SIZE> XOboard;


std::unordered_map<std::string, int> s = {
	{"X", 1}, // maximizing player
	{"O", -1},// minimizing player
	{"draw", 0},
};



XOboard InitBoard() {
	XOboard  board{ {} };
	int n = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i + j * SIZE] = std::to_string(++n);
		}
	}
	return board;
}

void printboard(XOboard& x) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << x[i+j*3] << "  ";
		}
		std::cout << std::endl;
	}
}

bool makemove(XOboard& x, std::string& player, std::string& move) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (x[i + j * SIZE] == move) {
				x[i + j * SIZE] = player;
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
			if (x[i + j * SIZE] != "O" && x[i + j * SIZE] != "X")
				res++;
	return res;
}

std::string checkwinner(XOboard& board) {
	std::string a[2] = { {"O"}, {"X"} };
	for (std::string player : a) {
		for (int i = 0; i < SIZE; i++) {
			if ((board[i] == player && board[i + 1 * SIZE] == player && board[i + 2 * SIZE] == player) || (board[i * SIZE] == player && board[1 + i * SIZE] == player && board[2 + i * SIZE] == player)) {
				return player;
			}
		}
		if ((board[0] == player && board[1 + 1 * SIZE] == player && board[2 + 2 * SIZE] == player) || (board[2] == player && board[1 + 1 * SIZE] == player && board[2 * SIZE] == player)) {
			return player;
		}
	}
	return checkEmpty(board) > 0 ? "" : "draw";
}

int minimax(XOboard& x, int depth, int alpha, int beta, bool maximizing) {
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
			bool continue_ = true;
			for (int i = 0; i < SIZE; i++) {
				if (!continue_)
					break;
				for (int j = 0; j < SIZE; j++) {
					if (x[i + j * SIZE] != "O" && x[i + j * SIZE] != "X") {
						std::string temp = x[i + j * SIZE];
						x[i + j * SIZE] = p;
						int attemptresult = minimax(x, depth + 1, alpha, beta, 0);
						x[i + j * SIZE] = temp;
						res = (std::max(res, attemptresult));
						alpha = std::max(attemptresult, alpha);
						if (beta <= alpha) {
							continue_ = false;
							break;
						}
					}
				}
			}
			return res;
		}
		else { // minimizing player
			int res = INT_MAX;
			bool continue_ = true;
			for (int i = 0; i < SIZE; i++) {
				if (!continue_)
					break;
				for (int j = 0; j < SIZE; j++) {
					if (x[i + j * SIZE] != "O" && x[i + j * SIZE] != "X") {
						std::string temp = x[i + j * SIZE];
						x[i + j * SIZE] = p;
						int attemptresult = minimax(x, depth + 1, alpha, beta, 1);
						x[i + j * SIZE] = temp;
						res = std::min(res, attemptresult);
						beta = std::min(attemptresult, beta);
						if (beta <= alpha) {
							continue_ = false;
							break;
						}
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
			if (x[i + j * SIZE] != "O" && x[i + j * SIZE] != "X") {
				std::string temp = x[i + j * SIZE];
				x[i + j * SIZE] = ai;
				int attemptresult = minimax(x, movenum + 1, INT_MIN, INT_MAX, 0);
				x[i + j * SIZE] = temp;
				if (attemptresult > res) {
					res = attemptresult;
					move.first = i;
					move.second = j;
				}
			}
		}
	}
	if (move.first >= 0 && move.second >= 0)
		x[move.first + move.second * SIZE] = ai;
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
		if (moves % 2 == 0) {
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
