#include "NumericalBoard.h"

bool NumericalBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    if (r < 0 || r > 2 || c < 0 || c > 2) {
        return false;
    }

    if (board[r][c] == 0) {
        board[r][c] = move->get_symbol();
        n_moves++;
        return true;
    }

    return false;
}

bool NumericalBoard::is_win(Player<char>* player) {
    for (int i = 0; i < 3; ++i) {
        if (get_cell_value(i, 0) + get_cell_value(i, 1) + get_cell_value(i, 2) == 15)
            return true;
    }

    for (int j = 0; j < 3; ++j) {
        if (get_cell_value(0, j) + get_cell_value(1, j) + get_cell_value(2, j) == 15)
            return true;
    }

    if (get_cell_value(0, 0) + get_cell_value(1, 1) + get_cell_value(2, 2) == 15)
        return true;

    if (get_cell_value(0, 2) + get_cell_value(1, 1) + get_cell_value(2, 0) == 15)
        return true;

    return false;
}

bool NumericalBoard::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool NumericalBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool NumericalBoard::is_lose(Player<char>* player) {
    return false;
}