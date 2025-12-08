#ifndef MEMORY_MINIMAX_PLAYER_H
#define MEMORY_MINIMAX_PLAYER_H

#include "BoardGame_Classes.h"
#include "MemoryBoard.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class MemoryMinimaxPlayer : public Player<T> {
public:
    MemoryMinimaxPlayer(string n, T symbol) : Player<T>(n, symbol, PlayerType::COMPUTER) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void get_move(int& x, int& y) {
        x = rand() % 3;
        y = rand() % 3;
    }
};

#endif