#ifndef OBSTACLESUI_H
#define OBSTACLESUI_H

#include "BoardGame_Classes.h"
#include <cstdlib>

// -------------------------------
//   AI PLAYER FOR OBSTACLES GAME
// -------------------------------
class AIPlayer_Obstacles : public Player<char> {
public:
    AIPlayer_Obstacles(char sym)
        : Player<char>("AI", sym, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* b = this->get_board_ptr();
        int r, c;

        while (true) {
            r = rand() % b->get_rows();
            c = rand() % b->get_columns();

            if (b->get_cell(r, c) == '.')
                return new Move<char>(r, c, this->symbol);
        }
    }
};

// -------------------------------
//          UI CLASS
// -------------------------------
class ObstaclesUI : public UI<char> {
public:
    ObstaclesUI() : UI<char>(3) {}

    Move<char>* get_move(Player<char>* p) override {

        // AI MOVE
        if (p->get_type() == PlayerType::AI) {
            AIPlayer_Obstacles* ai = dynamic_cast<AIPlayer_Obstacles*>(p);
            return ai->get_move();
        }

        // HUMAN MOVE
        int r, c;
        cout << p->get_name() << " (" << p->get_symbol() << ") enter row and column: ";
        cin >> r >> c;
        return new Move<char>(r, c, p->get_symbol());
    }
};

#endif
