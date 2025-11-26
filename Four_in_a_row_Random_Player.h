#ifndef FOUR_IN_A_ROW_RANDOM_PLAYER_H
#define FOUR_IN_A_ROW_RANDOM_PLAYER_H

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>

template <typename T>
class Four_in_a_row_Random_Player : public Player<T> {
public:
    Four_in_a_row_Random_Player(T symbol) : Player<T>("Random Computer", symbol, PlayerType::COMPUTER) {
        this->name = "Random Computer";
        srand(static_cast<unsigned int>(time(0)));
    }
    void get_move(int& x, int& y) {
        y = rand() % 7;
        x = 0;
    }
};

#endif