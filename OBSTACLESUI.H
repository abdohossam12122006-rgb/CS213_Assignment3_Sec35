#ifndef OBSTACLESUI_H
#define OBSTACLESUI_H

#include "BoardGame_Classes.h"
#include <cstdlib>

/**
 * @class AIPlayer_Obstacles
 * @brief AI player for the Obstacles game. Selects random valid empty cells.
 */
class AIPlayer_Obstacles : public Player<char> {
public:
    /**
     * @brief Constructor for AI player.
     * @param sym Character symbol for the AI (X/O).
     */
    AIPlayer_Obstacles(char sym)
        : Player<char>("AI", sym, PlayerType::AI) {}

    /**
     * @brief Generates a move for the AI by selecting a random empty cell.
     * @return Pointer to a dynamically allocated Move object.
     */
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

/**
 * @class ObstaclesUI
 * @brief User Interface class for the Obstacles game. Handles input for both human and AI.
 */
class ObstaclesUI : public UI<char> {
public:
    /**
     * @brief Constructor for ObstaclesUI.
     */
    ObstaclesUI() : UI<char>(3) {}

    /**
     * @brief Gets a move from either the human or AI player.
     * @param p Pointer to the player making the move.
     * @return Pointer to a new Move object.
     */
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
