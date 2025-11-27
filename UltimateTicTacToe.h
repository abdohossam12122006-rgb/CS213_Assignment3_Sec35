#pragma once
#ifndef ULTIMATE_TICTACTOE_H
#define ULTIMATE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

using namespace std;

class UltimateBoard : public Board<char> {
private:
    char meta_board[3][3];

public:
    UltimateBoard() : Board<char>(9, 9) {
        this->n_moves = 0;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                this->board[i][j] = 0;
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                meta_board[i][j] = 0;
            }
        }
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char symbol = move->get_symbol();

        if (x < 0 || x >= 9 || y < 0 || y >= 9 || this->board[x][y] != 0) {
            return false;
        }
        int meta_r = x / 3;
        int meta_c = y / 3;

        if (meta_board[meta_r][meta_c] != 0) {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;

        if (check_mini_board_win(meta_r, meta_c, symbol)) {
            meta_board[meta_r][meta_c] = symbol; 
        }

        return true;
    }

    bool check_mini_board_win(int mr, int mc, char symbol) {
        int start_r = mr * 3;
        int start_c = mc * 3;

        for (int i = 0; i < 3; i++) {
            if (board[start_r + i][start_c] == symbol &&
                board[start_r + i][start_c + 1] == symbol &&
                board[start_r + i][start_c + 2] == symbol) return true;
        }
        for (int j = 0; j < 3; j++) {
            if (board[start_r][start_c + j] == symbol &&
                board[start_r + 1][start_c + j] == symbol &&
                board[start_r + 2][start_c + j] == symbol) return true;
        }
        if (board[start_r][start_c] == symbol &&
            board[start_r + 1][start_c + 1] == symbol &&
            board[start_r + 2][start_c + 2] == symbol) return true;

        if (board[start_r][start_c + 2] == symbol &&
            board[start_r + 1][start_c + 1] == symbol &&
            board[start_r + 2][start_c] == symbol) return true;

        return false;
    }

    bool is_win(Player<char>* p) override {
        char s = p->get_symbol();

        for (int i = 0; i < 3; i++) {
            if (meta_board[i][0] == s && meta_board[i][1] == s && meta_board[i][2] == s) return true;
        }
        for (int j = 0; j < 3; j++) {
            if (meta_board[0][j] == s && meta_board[1][j] == s && meta_board[2][j] == s) return true;
        }
        if (meta_board[0][0] == s && meta_board[1][1] == s && meta_board[2][2] == s) return true;
        if (meta_board[0][2] == s && meta_board[1][1] == s && meta_board[2][0] == s) return true;

        return false;
    }

    bool is_lose(Player<char>* p) override { return false; }

    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 81 && !is_win(p));
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};

#endif