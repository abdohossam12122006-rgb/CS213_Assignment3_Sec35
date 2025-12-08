#pragma once
#ifndef MEMORY_BOARD_H
#define MEMORY_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

using namespace std;

class MemoryBoard : public Board<char> {
public:
    MemoryBoard() : Board<char>(3, 3) {
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
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || this->board[x][y] != 0) {
            return false;
        }

        this->board[x][y] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    bool is_win(Player<char>* p) override {
        char symbol = p->get_symbol();
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        }
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) return true;
        }
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;

        return false;
    }

    bool is_lose(Player<char>* p) override { return false; }

    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 9 && !is_win(p));
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};

#endif