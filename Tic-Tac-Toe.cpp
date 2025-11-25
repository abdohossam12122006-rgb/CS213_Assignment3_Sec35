#include "Tic-Tac-Toe.h" 
#include "BoardGame_Classes.h" 
#include <iostream>
#include <iomanip>
#include <cctype>
#include <random>
MemoryXO_Board::MemoryXO_Board() : Board(3, 3) {
    blank_symbol = '?';
    actual_board.resize(3, vector<char>(3, '.'));

    
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool MemoryXO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (actual_board[x][y] != '.')  
        return false;

    
    actual_board[x][y] = sym;

    
    board[x][y] = blank_symbol;

    n_moves++;
    return true;
}

bool MemoryXO_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    
    for (int i = 0; i < 3; i++) {
        if (actual_board[i][0] == s && actual_board[i][1] == s && actual_board[i][2] == s) return true;
        if (actual_board[0][i] == s && actual_board[1][i] == s && actual_board[2][i] == s) return true;
    }
    
    if (actual_board[0][0] == s && actual_board[1][1] == s && actual_board[2][2] == s) return true;
    if (actual_board[0][2] == s && actual_board[1][1] == s && actual_board[2][0] == s) return true;

    return false;
}

bool MemoryXO_Board::is_lose(Player<char>* p) {
    return false;  
}

bool MemoryXO_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool MemoryXO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

MemoryXO_UI::MemoryXO_UI() : UI<char>("Welcome to Memory Hidden XO Game", 3) {}

Player<char>* MemoryXO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryXO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter your move (row and column 0-2): ";
        cin >> x >> y;
    }
    else {
        
        x = rand() % 3;
        y = rand() % 3;
    }

    return new Move<char>(x, y, player->get_symbol());
}

