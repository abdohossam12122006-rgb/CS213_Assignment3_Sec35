# ifndef INFINITY_H
#define  INFINITY_H
using namespace std;
#include <iostream>
#include "BoardGame_Classes.h"
#include <iomanip>
#include <algorithm>
#include <vector>
#include <deque>
#include <limits>
class Infinity_Board :public Board<char> {
	struct MoveDetail {
		int x, y;
		char symbol;
	};
	std::deque<MoveDetail> history;

public:
	Infinity_Board() : Board<char>(3, 3) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				this->board[i][j] = 0; 
			}
		}
		  this->n_moves = 0;

	}
	bool update_board(Move <char>* move) override {
		int x = move->get_x();
		int y = move->get_y();
		char symbol = move->get_symbol();
		if (x < 0 || x >= this->rows || y<0 || y >= this->columns || this->board[x][y] != 0) {
			return false;
		}
		this->board[x][y] = symbol;
		this->n_moves++;
		history.push_back({ x, y, symbol });
		if (history.size() > 6) {
			MoveDetail oldest = history.front();
			this->board[oldest.x][oldest.y] = 0;
			history.pop_front();
		}
		return true;
	}
	bool is_win(Player<char>*p) override {
		char s = p->get_symbol();
		for (int i = 0; i < 3; i++) {
			//===columes===
			if (this->board[0][i] == s && this->board[1][i] == s && this->board[2][i] == s)return true;
			//===rows===
			if (this->board[i][0] == s && this->board[i][1] == s && this->board[i][2] == s)return true;
		}
		// Diagonal
		if (this->board[0][0] == s && this->board[1][1] == s && this->board[2][2] == s) return true; 
		if (this->board[0][2] == s && this->board[1][1] == s && this->board[2][0] == s) return true;
		
		return false;
	}
	bool is_lose(Player<char>* p)override {
		return false;
	}
	bool is_draw(Player<char>* player) override {

		if (this->n_moves >= 100) return true;
		return false;
	}
	bool game_is_over(Player<char>* player) override {
	
		return is_win(player) || is_draw(player) || is_lose(player);
	}
 };
//== InfinityUI ==
class InfinityUI : public UI<char> {
public:
	InfinityUI() : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 3) {}

	Player<char>* create_player(string& name, char symbol, PlayerType type) override {
		return new Player<char>(name, symbol, type);
	}

	Move<char>* get_move(Player<char>* p) override {
		int x, y;

		if (p->get_type() == PlayerType::COMPUTER) {
			cout << "\n" << p->get_name() << " (Computer) is thinking..." << endl;

			do {
				x = std::rand() % 3;
				y = std::rand() % 3;
			} while (p->get_board_ptr()->get_cell(x, y) != 0); // كرر حتى تجد خلية فارغة

			cout << "Computer plays at (" << x << ", " << y << ")" << endl;
			return new Move<char>(x, y, p->get_symbol());
		}

		else {
			cout << "\n" << p->get_name() << " (" << p->get_symbol() << "), enter row (0-2) and col (0-2): ";

			while (!(std::cin >> x >> y)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Invalid input. Please enter numbers: ";
			}
			return new Move<char>(x, y, p->get_symbol());
		}
	}
};

#endif 


