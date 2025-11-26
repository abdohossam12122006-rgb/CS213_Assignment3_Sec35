#ifndef NUMERICAL_BOARD_H
#define NUMERICAL_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class NumericalBoard : public Board<char> {
protected:
    vector<int> used_numbers;

public:
    NumericalBoard() : Board<char>(3, 3) {
        this->n_moves = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        int number = move->get_symbol() - '0';

        if (x < 0 || x >= 3 || y < 0 || y >= 3 || this->board[x][y] != 0) {
            return false;
        }

        if (number < 1 || number > 9) return false;

        if (find(used_numbers.begin(), used_numbers.end(), number) != used_numbers.end()) {
            return false;
        }

        bool is_player1_turn = (this->n_moves % 2 == 0);

        if (is_player1_turn && (number % 2 == 0)) return false;
        if (!is_player1_turn && (number % 2 != 0)) return false;

        this->board[x][y] = move->get_symbol();
        used_numbers.push_back(number);
        this->n_moves++;
        return true;
    }

    int get_cell_val(int x, int y) {
        if (board[x][y] == 0) return 0;
        return board[x][y] - '0';
    }

    bool is_win(Player<char>* p) override {
        for (int i = 0; i < 3; i++) {
            if (get_cell_val(i, 0) + get_cell_val(i, 1) + get_cell_val(i, 2) == 15 &&
                board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) return true;
        }
        for (int j = 0; j < 3; j++) {
            if (get_cell_val(0, j) + get_cell_val(1, j) + get_cell_val(2, j) == 15 &&
                board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0) return true;
        }
        if (get_cell_val(0, 0) + get_cell_val(1, 1) + get_cell_val(2, 2) == 15 &&
            board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) return true;

        if (get_cell_val(0, 2) + get_cell_val(1, 1) + get_cell_val(2, 0) == 15 &&
            board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) return true;

        return false;
    }

    bool is_lose(Player<char>* p) override {
        return false;
    }

    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 9 && !is_win(p));
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};

#endif