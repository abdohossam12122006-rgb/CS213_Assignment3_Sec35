#ifndef FOUR_IN_A_ROW_RANDOM_PLAYER_H
#define FOUR_IN_A_ROW_RANDOM_PLAYER_H

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>

/**
 * @class Four_in_a_row_Random_Player
 * @brief A computer-controlled player that selects random valid moves for the Connect Four game.
 *
 * This player chooses a random column (0–6) for its move.  
 * The row is always returned as 0 because gravity in the board will determine the actual row.
 *
 * @tparam T Symbol type (usually char).
 */
template <typename T>
class Four_in_a_row_Random_Player : public Player<T> {
public:
    /**
     * @brief Constructs a random computer player.
     *
     * @param symbol Symbol representing the player on the board.
     *
     * Initializes the random seed and sets the player type to COMPUTER.
     */
    Four_in_a_row_Random_Player(T symbol)
        : Player<T>("Random Computer", symbol, PlayerType::COMPUTER) 
    {
        this->name = "Random Computer";
        srand(static_cast<unsigned int>(time(0)));  ///< Seed RNG
    }

    /**
     * @brief Generates a random move for the player.
     *
     * @param x Output parameter for the row (set to 0; real row chosen by board gravity).
     * @param y Output parameter for the chosen column (0–6).
     *
     * This function does not check validity.  
     * The board class will reject invalid moves (e.g., full column).
     */
    void get_move(int& x, int& y) {
        y = rand() % 7;   ///< Random column between 0 and 6
        x = 0;            ///< Row placeholder (board will compute final row)
    }
};

#endif
