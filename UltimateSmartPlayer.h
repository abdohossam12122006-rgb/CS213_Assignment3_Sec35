#ifndef ULTIMATE_SMART_PLAYER_H
#define ULTIMATE_SMART_PLAYER_H

#include "BoardGame_Classes.h"
#include "UltimateTicTacToe.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class UltimateSmartPlayer : public Player<T> {
public:
    UltimateSmartPlayer(string n, T symbol) : Player<T>(n, symbol, PlayerType::COMPUTER) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void get_move(int& x, int& y) {
        UltimateBoard* currentBoard = dynamic_cast<UltimateBoard*>(this->boardPtr);

        if (!currentBoard) {
            x = rand() % 9;
            y = rand() % 9;
            return;
        }

        T mySymbol = this->symbol;
        do {
            x = rand() % 9;
            y = rand() % 9;
        } while (false); 
    }
};

#endif