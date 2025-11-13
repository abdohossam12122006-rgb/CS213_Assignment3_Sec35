#pragma once
#include "BoardGame_Classes.h"
#include "NumericalPlayer.h"

class NumericalUI : public UI<char>
{
public:
    NumericalUI() : UI("Welcome to Numerical Tic-Tac-Toe!", 3) {}

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};