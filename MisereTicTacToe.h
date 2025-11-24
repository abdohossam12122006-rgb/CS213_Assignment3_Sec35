#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

using namespace std;

class MisereBoard : public Board<char> {
public:
    MisereBoard() : Board<char>(3, 3) {
        this->n_moves = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }

    void undo_move(int x, int y) {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
            this->board[x][y] = 0;
            this->n_moves--;
        }
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

    bool is_win(Player<char>* player) override {
        return false;
    }

    bool is_lose(Player<char>* player) override {
        char symbol = player->get_symbol();

        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] != 0 &&
                this->board[i][0] == symbol &&
                this->board[i][1] == symbol &&
                this->board[i][2] == symbol) {
                return true;
            }
        }

        for (int j = 0; j < this->columns; j++) {
            if (this->board[0][j] != 0 &&
                this->board[0][j] == symbol &&
                this->board[1][j] == symbol &&
                this->board[2][j] == symbol) {
                return true;
            }
        }

        if (this->board[0][0] != 0 &&
            this->board[0][0] == symbol &&
            this->board[1][1] == symbol &&
            this->board[2][2] == symbol) {
            return true;
        }

        if (this->board[0][2] != 0 &&
            this->board[0][2] == symbol &&
            this->board[1][1] == symbol &&
            this->board[2][0] == symbol) {
            return true;
        }

        return false;
    }

    bool is_draw(Player<char>* player) override {
        return (this->n_moves == 9 && !is_lose(player));
    }

    bool game_is_over(Player<char>* player) override {
        return is_lose(player) || is_draw(player);
    }
};

#endif