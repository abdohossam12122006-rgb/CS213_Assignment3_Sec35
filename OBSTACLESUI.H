#ifndef OBSTACLESUI_H
#define OBSTACLESUI_H

#include "BoardGame_Classes.h"

class ObstaclesUI : public UI<char> {
public:
    ObstaclesUI() : UI<char>(3) {}

    Move<char>* get_move(Player<char>* p) override {
        int r, c;
        cout << p->get_name() << " (" << p->get_symbol() << ") enter row and column: ";
        cin >> r >> c;

        return new Move<char>(r, c, p->get_symbol());
    }
};

#endif

