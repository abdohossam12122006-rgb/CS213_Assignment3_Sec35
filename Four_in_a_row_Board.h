#ifndef FOUR_IN_A_ROW_BOARD_H
#define FOUR_IN_A_ROW_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @class Four_in_a_row_Board
 * @brief Represents the board for the Connect Four game (6 rows × 7 columns).
 *
 * Handles move placement, win checking, draw detection, and full game state evaluation.
 */
class Four_in_a_row_Board : public Board<char> {
public:
    /**
     * @brief Constructs a 6×7 Connect Four board and initializes all cells to empty (0).
     */
    Four_in_a_row_Board() : Board<char>(6, 7) {
        this->n_moves = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }

    /**
     * @brief Inserts a player's piece into the chosen column (gravity-based drop).
     *
     * @param move Pointer to Move object containing column and symbol.
     * @return true if move is valid and successfully placed, false otherwise.
     *
     * The piece falls to the lowest empty row in the chosen column.
     */
    bool update_board(Move<char>* move) override {
        int y = move->get_y();

        if (y < 0 || y >= this->columns) {
            return false;  ///< Column out of bounds
        }

        int validRow = -1;

        /// @brief Find the lowest empty row in the selected column
        for (int i = this->rows - 1; i >= 0; i--) {
            if (this->board[i][y] == 0) {
                validRow = i;
                break;
            }
        }

        if (validRow == -1) {
            return false;  ///< Column is full
        }

        this->board[validRow][y] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    /**
     * @brief Checks if the given player has achieved a 4-symbol connection.
     *
     * @param p Pointer to the player whose symbol is checked.
     * @return true if the player has four in a row (horizontal, vertical, diagonal, or anti-diagonal).
     */
    bool is_win(Player<char>* p) override {
        char symbol = p->get_symbol();

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != symbol) continue;

                /// @brief Horizontal check
                if (j + 3 < this->columns &&
                    this->board[i][j + 1] == symbol &&
                    this->board[i][j + 2] == symbol &&
                    this->board[i][j + 3] == symbol) return true;

                /// @brief Vertical check
                if (i + 3 < this->rows &&
                    this->board[i + 1][j] == symbol &&
                    this->board[i + 2][j] == symbol &&
                    this->board[i + 3][j] == symbol) return true;

                /// @brief Diagonal (bottom-right) check
                if (i + 3 < this->rows && j + 3 < this->columns &&
                    this->board[i + 1][j + 1] == symbol &&
                    this->board[i + 2][j + 2] == symbol &&
                    this->board[i + 3][j + 3] == symbol) return true;

                /// @brief Anti-diagonal (bottom-left) check
                if (i + 3 < this->rows && j - 3 >= 0 &&
                    this->board[i + 1][j - 1] == symbol &&
                    this->board[i + 2][j - 2] == symbol &&
                    this->board[i + 3][j - 3] == symbol) return true;
            }
        }
        return false;
    }

    /**
     * @brief Checks if the player has lost.
     *
     * @param p Pointer to the player.
     * @return Always false (losing is not directly tracked in this implementation).
     */
    bool is_lose(Player<char>* p) override {
        return false;
    }

    /**
     * @brief Checks if the game is a draw.
     *
     * @param p Pointer to the player (unused).
     * @return true if the board is full (42 moves) and there is no win.
     */
    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 42 && !is_win(p));
    }

    /**
     * @brief Checks whether the game is over.
     *
     * @param p Pointer to the current player.
     * @return true if the game ended by either win or draw.
     */
    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};

#endif
