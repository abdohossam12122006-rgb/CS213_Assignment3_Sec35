#ifndef FIVE_BY_FIVE_BOARD_H
#define FIVE_BY_FIVE_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

using namespace std;

class FiveByFiveBoard : public Board<char> {
public:
    FiveByFiveBoard() : Board<char>(5, 5) {
        this->n_moves = 0;

        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->columns; j++)
                this->board[i][j] = 0;
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false;
        }

        this->board[x][y] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    int count_three_in_a_row(char symbol) {
        int count = 0;

        // Horizontal
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j <= 2; j++) {
                if (this->board[i][j] == symbol &&
                    this->board[i][j + 1] == symbol &&
                    this->board[i][j + 2] == symbol) {
                    count++;
                }
            }
        }

        // Vertical
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i <= 2; i++) {
                if (this->board[i][j] == symbol &&
                    this->board[i + 1][j] == symbol &&
                    this->board[i + 2][j] == symbol) {
                    count++;
                }
            }
        }

        // Main diagonal
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                if (this->board[i][j] == symbol &&
                    this->board[i + 1][j + 1] == symbol &&
                    this->board[i + 2][j + 2] == symbol)
                    count++;
            }
        }

        // Anti diagonal
        for (int i = 0; i <= 2; i++) {
            for (int j = 2; j < 5; j++) {
                if (this->board[i][j] == symbol &&
                    this->board[i + 1][j - 1] == symbol &&
                    this->board[i + 2][j - 2] == symbol)
                    count++;
            }
        }

        return count;
    }

    bool is_win(Player<char>* p) override {
        if (this->n_moves < 24) return false;

        char my_symbol = p->get_symbol();
        char opp_symbol = 0;

        // Find opponent symbol
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] != 0 && board[i][j] != my_symbol) {
                    opp_symbol = board[i][j];
                    break;
                }
            }
            if (opp_symbol != 0) break;
        }

        if (opp_symbol == 0) return false;

        return count_three_in_a_row(my_symbol) > count_three_in_a_row(opp_symbol);
    }

    bool is_draw(Player<char>* p) override {
        if (this->n_moves < 24) return false;
        return !is_win(p);
    }

    bool game_is_over(Player<char>* p) override {
        return this->n_moves == 24;
    }
    bool is_lose(Player<char>* p) override {
        return !is_win(p) && game_is_over(p);
    }
};

#endif
