#ifndef GAME_7__H
#define GAME_7__H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;
class Game7_Board : public Board<char> {
public:
	//====move implemantation func===
	Game7_Board() : Board<char>(4, 4) {
		this->n_moves = 0;
	}

	bool update_board(Move<char>* move) override {
		int x = move->get_x();
		int y = move->get_y();
		char symbol = move->get_symbol();

		if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
			return false;
		}

		if (this->board[x][y] == 0) { 
			this->board[x][y] = symbol;
			this->n_moves++;
			return true;
		}
		return false;
	}

	//===win func===
	bool is_win(Player<char>* p) override {
		char symbol = p->get_symbol();
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {

				// 1. horizontal (3 رموز متتالية)
			
				if (j + 2 < this->columns &&
					this->board[i][j] == symbol &&
					this->board[i][j + 1] == symbol &&
					this->board[i][j + 2] == symbol) {
					return true;
				}

				// 2. vertical 
				if (i + 2 < this->rows &&
					this->board[i][j] == symbol &&
					this->board[i + 1][j] == symbol &&
					this->board[i + 2][j] == symbol) {
					return true;
				}

				// 3. Diagonal Down-Right 
				if (i + 2 < this->rows && j + 2 < this->columns &&
					this->board[i][j] == symbol &&
					this->board[i + 1][j + 1] == symbol &&
					this->board[i + 2][j + 2] == symbol) {
					return true;
				}

				// 4. Diagonal Down-Left
				if (i + 2 < this->rows && j - 2 >= 0 &&
					this->board[i][j] == symbol &&
					this->board[i + 1][j - 1] == symbol &&
					this->board[i + 2][j - 2] == symbol) {
					return true;
				}
			}
		}

		return false;
	}

	bool is_draw(Player<char>* p) override {
		return (this->n_moves == 16 && !is_win(p));
	}

	bool game_is_over(Player<char>* p) override {
		return is_win(p) || is_draw(p);
	}

	bool is_lose(Player<char>* p) override {
		return false;
	}
};

//=== Game 7 UI Class ===
class Game7_UI : public UI<char> {
public:
	Game7_UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe (Game 7)!", 4) {}

	Player<char>* create_player(string& name, char symbol, PlayerType type) override {
		return new Player<char>(name, symbol, type);
	}

	Move<char>* get_move(Player<char>* p) override {
		int x, y;

		if (p->get_type() == PlayerType::HUMAN) {
			cout << "\n" << p->get_name() << " (" << p->get_symbol() << "), enter your move (row and column 0-3): ";
			cin >> x >> y;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter numbers: ";
				cin >> x >> y;
			}
		}
		else {
			x = rand() % 4;
			y = rand() % 4;
		}

		return new Move<char>(x, y, p->get_symbol());
	}
};

#endif // GAME_7__H
