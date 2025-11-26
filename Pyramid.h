#ifndef PYRAMID_H
#define PYRAMID_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

class Pyramid_Board : public Board<char> {
public:
	Pyramid_Board() : Board<char>(3, 5) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				this->board[i][j] = 0;
			}
		}
		this->n_moves = 0;
	} 
	
	//===move implementation===
	bool update_board(Move<char>* move)override {
		int r = move->get_x();
		int c = move->get_y();
		char symbol = move->get_symbol();
		  
		
		if (r < 0 || r >= this->rows || c < 0 || c >= this->columns) {
			return false;
		}

		// 2. التحقق من الشكل الهرمي 
		bool is_valid_square = false;
		if (r == 0 && c == 2) {
			is_valid_square = true; // القمة
		}
		else if (r == 1 && (c == 1 || c == 2 || c == 3)) {
			is_valid_square = true; // الوسط
		}
		else if (r == 2 && c < 5) { 
			is_valid_square = true; // القاعدة
		}

		if (!is_valid_square) {
			return false;
		}

		// 3. التحقق من أن الخانة فارغة
		if (this->board[r][c] == 0) {
			this->board[r][c] = symbol; 
			this->n_moves++;
			return true;
		}
		return false; 
	}
	//===win function===
	bool is_win(Player<char>* p)override {
		char symbol = p->get_symbol();
		//===vertical ===
		if (this->board[0][2] == symbol &&
			this->board[1][2] == symbol &&
			this->board[2][2] == symbol) {
			return true;
		}
		//===Diagonal down right ===
		if (this->board[0][2] == symbol &&
			this->board[1][1] == symbol &&
			this->board[2][0] == symbol) {
			return true;
		}
		//===Diagonal down left ===
		if (this->board[0][2] == symbol &&
			this->board[1][3] == symbol &&
			this->board[2][4] == symbol) {
			return true;
		}
		//===HORIZONTAL 1===
		if (this->board[1][1] == symbol &&
			this->board[1][2] == symbol &&
			this->board[1][3] == symbol) {
			return true;
		}
		//===HORIZONTAL2 ===
		for (int c = 0; c <= 2; ++c) {
			if (this->board[2][c] == symbol &&
				this->board[2][c + 1] == symbol &&
				this->board[2][c + 2] == symbol) {
				return true;
			}
		}
		return false;
	}
	bool is_draw(Player<char>* p) override {
		return (this->n_moves == 9 && !is_win(p));
	}
	bool game_is_over(Player<char>* p) override {
		return is_win(p) || is_draw(p);
	}
	bool is_lose(Player<char>* p) override {
		return false;
	}
};
class Pyramid_UI : public UI<char> {
public:
	Pyramid_UI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe (Game 8)!", 3) {
	}

	Player<char>* create_player(string& name, char symbol, PlayerType type) override {
		return new Player<char>(name, symbol, type);
	}

	Move<char>* get_move(Player<char>* p) override {
		int x, y;

		if (p->get_type() == PlayerType::HUMAN) {
			cout << "\n" << p->get_name() << " (" << p->get_symbol() << "), enter your move (row 0-2 and column 0-4): ";
			cin >> x >> y;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter numbers: ";
				cin >> x >> y;
			}
		}
		else {
			x = rand() % 3; 
			y = rand() % 5; 
		}

		return new Move<char>(x, y, p->get_symbol());
	}
};
#endif
