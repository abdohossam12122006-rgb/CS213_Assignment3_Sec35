#ifndef DIAMOND_BOARD_H
#define DIAMOND_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class DiamondBoard : public Board<char> {
public:
    DiamondBoard() : Board<char>(5, 5) {
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

    bool is_inside_diamond(int x, int y) const {
        return (abs(x - 2) + abs(y - 2)) <= 2;
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char symbol = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (!is_inside_diamond(x, y)) return false;
        if (this->board[x][y] != 0) return false;

        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void check_line_segment(int start_x, int start_y, int dx, int dy, char symbol, bool& has3, bool& has4) {
        int count = 0;
        int x = start_x;
        int y = start_y;
        while (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
            if (is_inside_diamond(x, y) && this->board[x][y] == symbol) count++;
            else {
                if (count == 3) has3 = true;
                if (count >= 4) has4 = true;
                count = 0;
            }
            x += dx;
            y += dy;
        }
        if (count == 3) has3 = true;
        if (count >= 4) has4 = true;
    }

    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        bool dir3[4] = { 0 }, dir4[4] = { 0 };

        for (int i = 0; i < 5; i++) check_line_segment(i, 0, 0, 1, symbol, dir3[0], dir4[0]);
        for (int j = 0; j < 5; j++) check_line_segment(0, j, 1, 0, symbol, dir3[1], dir4[1]);

        check_line_segment(2, 0, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(1, 0, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(0, 0, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(0, 1, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(0, 2, 1, 1, symbol, dir3[2], dir4[2]);

        check_line_segment(2, 4, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(1, 4, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(0, 4, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(0, 3, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(0, 2, 1, -1, symbol, dir3[3], dir4[3]);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i != j && dir3[i] && dir4[j]) return true;
            }
        }
        return false;
    }

    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return (this->n_moves == 13 && !is_win(player)); }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

#endif // DIAMOND_BOARD_H
#endif // DIAMOND_BOARD_H
