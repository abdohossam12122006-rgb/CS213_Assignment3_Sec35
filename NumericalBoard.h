#pragma once
#include "BoardGame_Classes.h"

class NumericalBoard : public Board<char>
{
public:
    NumericalBoard() : Board(3, 3) {}

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;

    int get_cell_value(int r, int c) {
        if (board[r][c] >= '1' && board[r][c] <= '9') {
            return board[r][c] - '0';
        }
        return 0;
    }
};