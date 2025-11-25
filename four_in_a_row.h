#ifndef FOUR_IN_A_ROW_BOARD_H
#define FOUR_IN_A_ROW_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

using namespace std;

class Four_in_a_row_Board : public Board<char> {
public:
    Four_in_a_row_Board() : Board<char>(6, 7) {
        this->n_moves = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }

    bool update_board(Move<char>* move) override {
        int y = move->get_y();

        if (y < 0 || y >= this->columns) {
            return false;
        }

        int validRow = -1;
        for (int i = this->rows - 1; i >= 0; i--) {
            if (this->board[i][y] == 0) {
                validRow = i;
                break;
            }
        }

        if (validRow == -1) {
            return false;
        }
        this->board[validRow][y] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    bool is_win(Player<char>* p) override {
        char symbol = p->get_symbol(); 

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != symbol) continue;

                if (j + 3 < this->columns &&
                    this->board[i][j + 1] == symbol &&
                    this->board[i][j + 2] == symbol &&
                    this->board[i][j + 3] == symbol) return true;

                if (i + 3 < this->rows &&
                    this->board[i + 1][j] == symbol &&
                    this->board[i + 2][j] == symbol &&
                    this->board[i + 3][j] == symbol) return true;

                if (i + 3 < this->rows && j + 3 < this->columns &&
                    this->board[i + 1][j + 1] == symbol &&
                    this->board[i + 2][j + 2] == symbol &&
                    this->board[i + 3][j + 3] == symbol) return true;

                if (i + 3 < this->rows && j - 3 >= 0 &&
                    this->board[i + 1][j - 1] == symbol &&
                    this->board[i + 2][j - 2] == symbol &&
                    this->board[i + 3][j - 3] == symbol) return true;
            }
        }
        return false;
    }

    bool is_lose(Player<char>* p) override {
        return false;
    }

    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 42 && !is_win(p));
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};

#endif
