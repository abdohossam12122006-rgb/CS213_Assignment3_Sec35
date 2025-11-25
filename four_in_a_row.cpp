#include "four_in_a_row.h"
#include <iostream>
#include <iomanip>
#include <cctype> 
#include <vector> 
#include <random>
using namespace std; 
Connect4Board::Connect4Board() : Board<char>(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Connect4Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    if (col < 0 || col >= columns) return false;

    
    for (int r = rows - 1; r >= 0; --r) {
        if (board[r][col] == blank_symbol) {
            board[r][col] = mark;
            n_moves++;
            return true;
        }
    }
    return false; 
}


bool check_dir(const vector<vector<char>>& board, int r, int c, int dr, int dc, char sym) {
    int count = 0;
    int rr = r, cc = c;


    while (rr >= 0 && rr < (int)board.size() && cc >= 0 && cc < (int)board[0].size() && board[rr][cc] == sym) {
        rr -= dr; cc -= dc;
    }
    rr += dr; cc += dc;

    while (rr >= 0 && rr < (int)board.size() && cc >= 0 && cc < (int)board[0].size() && board[rr][cc] == sym) {
        count++;
        if (count >= 4) return true;
        rr += dr; cc += dc;
    }
    return false;
}

bool Connect4Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (board[r][c] != sym) continue;
            if (check_dir(board, r, c, 0, 1, sym)) return true;   
            if (check_dir(board, r, c, 1, 0, sym)) return true;   
            if (check_dir(board, r, c, 1, 1, sym)) return true;   
            if (check_dir(board, r, c, -1, 1, sym)) return true;  
        }
    }
    return false;
}

bool Connect4Board::is_lose(Player<char>* player) {
    char other = (player->get_symbol() == 'X') ? 'O' : 'X';
    
    class TempP : public Player<char> {
    public:
        TempP(char s) : Player<char>("", s, PlayerType::RANDOM) {}
    };
    TempP tmp(other);
    return is_win(&tmp);
}

bool Connect4Board::is_draw(Player<char>* player) {
    return n_moves >= rows * columns;
}

bool Connect4Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


Connect4UI::Connect4UI() : UI<char>("Welcome to Connect Four 2D Game!", 3) {}

Player<char>* Connect4UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Connect4UI::get_move(Player<char>* player) {
    int col = 0;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter column (0-" << player->get_board_ptr()->get_columns() - 1 << "): ";
        cin >> col;
    }
    else { 
        vector<int> avail;
        auto matrix = player->get_board_ptr()->get_board_matrix();
        for (int c = 0; c < player->get_board_ptr()->get_columns(); ++c)
            if (matrix[0][c] == '.') avail.push_back(c);
        if (!avail.empty()) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, avail.size() - 1);
            col = avail[dis(gen)];
        }
    }
    return new Move<char>(-1, col, player->get_symbol()); 

}
