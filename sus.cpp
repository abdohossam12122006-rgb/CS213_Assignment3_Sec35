#include "sus.h"
#include <cctype> 

SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = toupper(mark);
    n_moves++;
    return true;
}

int SUS_Board::count_sequences(char symbol) {
    int count = 0;

    // Directions to check (horizontal, vertical, diagonals)
    int dir[4][2] = {
        {1, 0}, {0, 1}, {1, 1}, {1, -1}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            for (auto& d : dir) {
                int x1 = i, y1 = j;
                int x2 = i + d[0], y2 = j + d[1];
                int x3 = i + 2 * d[0], y3 = j + 2 * d[1];

                if (x3 < 0 || x3 >= rows || y3 < 0 || y3 >= columns) continue;

                if (board[x1][y1] == 'S' && board[x2][y2] == 'U' && board[x3][y3] == 'S')
                    count++;
            }
        }
    }
    return count;
}

bool SUS_Board::is_win(Player<char>* player) {
    return false; // No instant win
}

bool SUS_Board::is_draw(Player<char>* player) {
    return (n_moves == 9);
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves == 9;
}

