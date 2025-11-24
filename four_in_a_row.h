#pragma once
#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H
#include "BoardGame_Classes.h" 
using namespace std;

class Connect4Board :public Board<char>
{
private:
    char blank_symbol = '.';
public:
    Connect4Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};
class Connect4UI : public UI<char> {
public:
    Connect4UI();
    ~Connect4UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

#endif
