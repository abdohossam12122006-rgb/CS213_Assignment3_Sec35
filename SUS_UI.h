#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the 3×3 board for the SUS game and handles the main logic.
 */
class SUS_Board : public Board<char> {
private:
    /**
     * @brief Symbol representing an empty cell.
     */
    char blank_symbol = '.';

public:
    /**
     * @brief Constructs a 3×3 SUS board and initializes it.
     */
    SUS_Board();

    /**
     * @brief Utility function that counts all completed "S-U-S" sequences in any matrix.
     *
     * @param mat 2D matrix of characters representing a board state.
     * @param symbol Player symbol (not used but kept for compatibility).
     * @return Number of detected sequences.
     */
    static int count_sequences_in_matrix(const std::vector<std::vector<char>>& mat, char symbol);

    /**
     * @brief Applies a move to the board if valid.
     *
     * @param move Pointer to a move containing x, y, and symbol.
     * @return True if the move was applied successfully.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks whether the player has won.
     *
     * @param player Pointer to a player.
     * @return Always false (SUS game uses scoring instead of win detection).
     */
    bool is_win(Player<char>* player) { return false; }

    /**
     * @brief Checks whether the player has lost.
     *
     * @param player Pointer to a player.
     * @return Always false (SUS game uses scoring instead of lose detection).
     */
    bool is_lose(Player<char>* player) { return false; }

    /**
     * @brief Checks whether the game ended in a draw.
     *
     * @param player Pointer to the player (unused).
     * @return True if all cells are filled.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks whether the game is over.
     *
     * @param player Pointer to the player (unused).
     * @return True if no more moves can be played.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Counts all "S-U-S" sequences on the board.
     *
     * @param s Character symbol (unused).
     * @return Number of detected sequences.
     */
    int count_sequences(char s);
};

/**
 * @class SUS_AI
 * @brief AI-controlled player that evaluates board states and selects optimal moves.
 */
class SUS_AI : public Player<char> {
public:
    /**
     * @brief Constructs an AI player.
     *
     * @param name Name of the AI.
     * @param symbol Symbol representing the AI ('S' or 'U').
     */
    SUS_AI(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::AI) {}

    /**
     * @brief Computes the best possible move using evaluation heuristics.
     *
     * @return Pointer to the best Move object, or nullptr if no moves available.
     */
    Move<char>* get_best_move() {
        auto mat = this->boardPtr->get_board_matrix();
        int bestX = -1, bestY = -1;
        int bestValue = -999;

        for (int i = 0; i < this->boardPtr->get_rows(); i++) {
            for (int j = 0; j < this->boardPtr->get_columns(); j++) {

                if (mat[i][j] == '.') {

                    mat[i][j] = this->symbol;
                    int gain = evaluate(mat, this->symbol);
                    mat[i][j] = '.';

                    if (gain > bestValue) {
                        bestValue = gain;
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }
        if (bestX == -1) return nullptr;
        return new Move<char>(bestX, bestY, this->symbol);
    }

private:
    /**
     * @brief AI board evaluation function.
     *
     * @param mat Board matrix to evaluate.
     * @param me The AI's symbol.
     * @return A score representing the advantage of the board for the AI.
     */
    int evaluate(const std::vector<std::vector<char>>& mat, char me);
};

/**
 * @class SUS_UI
 * @brief Handles user interface interaction and player creation for the SUS game.
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructs the SUS UI with a welcome message and board size.
     */
    SUS_UI() : UI<char>("Welcome to SUS Game", 3) {}

    /**
     * @brief Creates a player (Human or AI) based on parameters.
     *
     * @param name Player name.
     * @param symbol Player symbol ('S' or 'U').
     * @param type Player type (Human or AI).
     * @return Pointer to a newly created player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::AI)
            return new SUS_AI(name, symbol);
        return new Player<char>(name, symbol, type);
    }

    /**
     * @brief Sets up both players by asking the user for name and type.
     *
     * @return Array of two player pointers.
     */
    Player<char>** setup_players() override;

    /**
     * @brief Handles user input or AI decision to get the next move.
     *
     * @param player The current player.
     * @return Pointer to a Move object chosen by the player.
     */
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            cout << player->get_name() << " (AI) is thinking...\n";
            return static_cast<SUS_AI*>(player)->get_best_move();
        }

        int x, y;
        cout << player->get_name() << " Enter x y: ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
};

#endif
